#!/usr/bin/python

import random
import pygtk
pygtk.require('2.0')
import gtk
import pango

class Exercise(object):
    def __init__(self, x, y, action):
        self.str = str(x) + ' ' + action + ' ' + str(y)
        self.answer = int(eval(self.str))
    def __str__(self):
        return self.str + '=' + self.answer
    def check(self, val):
        return int(val) == self.answer

class Settings(object):
    def __init__(self):
        self.min = 0
        self.max = 0
        self.actions = []
    def check(self):
        if self.min == self.max:
            return "min == max"
        if self.min < 0 or self.max < 0:
            return "min or max < 0"
        if self.min > self.max:
            return "min > max"
        if len(self.actions) == 0:
            return "no actions"
        return None

def gen_exercises(n, cfg):
    i = 0
    exercises = set()
    while len(exercises) != n:
        print cfg.min, cfg.max, cfg.actions
        e = Exercise(random.randint(cfg.min, cfg.max), random.randint(cfg.min, cfg.max), random.choice(cfg.actions))
        if e.answer < 0:
            continue
        exercises.add(e)
        i = i + 1
        if i > n*n:
            break
    return list(exercises)

class MathTrainer:

    def on_number_click(self, widget, data=None):
        self.l_answer.set_text(self.l_answer.get_text() + str(data))

    def on_clear_click(self, widget, data=None):
        self.l_answer.set_text('')
        self.l_answer.modify_fg(gtk.STATE_NORMAL, None)

    def on_go_click(self, widget, data=None):
        if str(self.exercises[self.idx].answer) == self.l_answer.get_text():
            self.next_exercise()
        else:
            print self.exercises[self.idx].answer, '!=', self.l_answer.get_text()
            self.l_answer.modify_text(gtk.STATE_NORMAL, gtk.gdk.color_parse('red'))
            self.l_answer.modify_fg(gtk.STATE_NORMAL, gtk.gdk.color_parse('red'))

    def on_start_training(self, widget, data=None):
        s = Settings()
        s.min = int(self.minNum.get_text())
        s.max = int(self.maxNum.get_text())
        if self.cbAdd.get_active():
            s.actions.append('+')
        if self.cbSubtract.get_active():
            s.actions.append('-')
        if self.cbMultiply.get_active():
            s.actions.append('*')
        if self.cbDivide.get_active():
            s.actions.append('/')
        err = s.check()
        if err:
            gtk.MessageDialog(None, gtk.DIALOG_MODAL, gtk.MESSAGE_ERROR, gtk.BUTTONS_NONE, err).show()
            return
        self.setup_training(s)

    def delete_event(self, widget, event, data=None):
        print "delete event occurred"

        # Change FALSE to TRUE and the main window will not be destroyed
        # with a "delete_event".
        return False

    def destroy(self, widget, data=None):
        print "destroy signal occurred"
        gtk.main_quit()

    def next_exercise(self):
        self.set_exercise(self.idx + 1)

    def set_exercise(self, idx):
        self.idx = idx
        self.l_exercise.set_text(self.exercises[idx].str)
        self.l_answer.set_text('')

    def set_main_vbox(self, vbox):
        if self.mainVbox:
            self.window.remove(self.mainVbox)
        self.mainVbox = vbox
        self.window.add(self.mainVbox)
        self.window.show_all()

    def setup_training(self, s):
        self.exercises = gen_exercises(10, s)
        self.idx = 0
        vbox = gtk.VBox(False, 5)
        valign = gtk.Alignment(0, 1, 0, 0)
        vbox.pack_start(valign)
        self.l_exercise = gtk.Label('exercise')
        fontdesc = pango.FontDescription('Terminus Bold 20')
        self.l_exercise.modify_font(fontdesc)
        vbox.add(self.l_exercise)
        self.l_answer = gtk.Label('<b>answer</b>')
        self.l_answer.modify_font(fontdesc)
        self.b_clear = gtk.Button("C")
        self.b_clear.connect("clicked", self.on_clear_click, None)
        self.b_go = gtk.Button("=")
        self.b_go.connect("clicked", self.on_go_click, None)
        vbox.add(self.l_answer)
        # Sets the border width of the window.
        self.window.set_border_width(10)

        self.buttons = []
        for i in range(0, 10):
            b = gtk.Button(str(i))
            b.connect("clicked", self.on_number_click, i)
            self.buttons.append(b)

        for i in range(0, 3):
            hbox = gtk.HBox(True, 3)
            for j in range(0, 3):
                hbox.add(self.buttons[3 * i + j])
            vbox.add(hbox)
        hbox = gtk.HBox(True, 3)
        hbox.add(self.b_clear)
        hbox.add(self.buttons[9])
        hbox.add(self.b_go)
        vbox.add(hbox)
        self.set_main_vbox(vbox)
        self.set_exercise(0)

    def setup_settings(self):
        vbox = gtk.VBox(False, 5)
        hbox = gtk.HBox(True, 4)
        self.cbAdd = gtk.CheckButton("+")
        self.cbSubtract = gtk.CheckButton("-")
        self.cbMultiply = gtk.CheckButton("*")
        self.cbDivide = gtk.CheckButton("/")
        hbox.add(self.cbAdd)
        hbox.add(self.cbSubtract)
        hbox.add(self.cbMultiply)
        hbox.add(self.cbDivide)
        vbox.add(hbox)
        hbox = gtk.HBox(True, 2)
        self.minNum = gtk.Entry(4)
        self.minNum.set_text("0")
        self.maxNum = gtk.Entry(4)
        self.maxNum.set_text("100")
        hbox.add(self.minNum)
        hbox.add(gtk.Label(" - "))
        hbox.add(self.maxNum)
        vbox.add(hbox)
        b = gtk.Button("Start")
        b.connect("clicked", self.on_start_training, None)
        vbox.add(b)
        self.set_main_vbox(vbox)

    def __init__(self):
        self.mainVbox = None
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.connect("delete_event", self.delete_event)
        self.window.connect("destroy", self.destroy)
        self.window.set_default_size(320, 240)

        self.setup_settings()
        # and the window

    def main(self):
        # All PyGTK applications must have a gtk.main(). Control ends here
        # and waits for an event to occur (like a key press or mouse event).
        gtk.main()

# If the program is run directly or passed as an argument to the python
# interpreter then create a MathTrainer instance and show it
if __name__ == "__main__":
    hello = MathTrainer()
    hello.main()

