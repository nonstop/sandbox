#!/usr/bin/env python

import os
import re
import sys
import shutil
import datetime
import subprocess
import getopt
from subprocess import Popen

def durationStr(d):
    return "{0}".format(datetime.timedelta(0, d))

def filesizeStr(sz):
    return "{0}M".format(round(sz / (1024. * 1024.), 1))

def imageFilenameStr(fn):
    posDot = fn.rfind('.')
    if posDot > 0:
        return fn[:posDot] + '.jpg'
    else:
        return fn + '.jpg'

def titleStr(s):
    ns = ''
    for w in s.split('_'):
        ns += ' ' + w.capitalize()
    return ns[1:]

class VideoAnalizer(object):
    def __init__(self, filename):
        self.filename = None
        cmd = 'mplayer -msglevel all=0 -identify -nosound -vc dummy -vo null "' + filename + '"'
        try: 
            self.filesize = os.stat(filename).st_size
        except OSError as e:
            print e
            return None
        print cmd
        proc = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, close_fds=True)
        out = proc.stdout
        l = out.readline()
        reh = re.compile(r".*HEIGHT=([0-9]+)")
        rew = re.compile(r".*WIDTH=([0-9]+)")
        rel = re.compile(r".*LENGTH=([0-9]+)")
        while l:
            l = l[:-1]
            m = reh.match(l)
            if m:
                self.height = int(m.group(1))
            else:
                m = rew.match(l)
                if m:
                    self.width = int(m.group(1))
                else:
                    m = rel.match(l)
                    if m:
                        self.duration = int(m.group(1))
            l = out.readline()

        cmd = 'ffmpeg -i "' + filename + '" 2>&1 '
        print cmd
        proc = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, close_fds=True)
        out = proc.stdout
        l = out.readline()
        rev = re.compile(r".*(Video:.*)")
        rea = re.compile(r".*(Audio:.*)")
        while l:
            l = l[:-1]
            m = rev.match(l)
            if m:
                self.video = m.group(1)
            else:
                m = rea.match(l)
                if m:
                    self.audio = m.group(1)
            l = out.readline()
        self.filename = os.path.basename(filename)
    def __str__(self):
        return "File: {0}\n{1} {2}x{3} {4}\n{5}\n{6}".format(
                self.filename, filesizeStr(self.filesize), self.width, self.height, durationStr(self.duration), self.video, self.audio)

#f = sys.argv[1]
#'/mnt/sandbox/tmpfiles/tmp/done/phoenix_marie_-_dirty_minds.avi'
#va = VideoAnalizer(f)
def rowsCols(d):
    minutes = d / 60
    if minutes == 12:
        return (4, 3)
    elif minutes < 20:
        return (5, 4)
    elif minutes < 25:
        return (6, 4)
    elif minutes < 30:
        return (6, 5)
    else:
        return (minutes / 5, 5)
#print durationStr(va.duration), rowsCols(va.duration)
#exit(0)

class ThumbsCreator(object):
    def __init__(self, filename, n, length, start = 5, end = None):
        dir = '/tmp/thumbs'
        if not os.path.exists(dir):
            os.mkdir(dir)
        else:
            ret = subprocess.call('rm {0}/*'.format(dir), shell=True, close_fds=True)
            if ret != 0:
                print 'ThumbsCreator clear {0} failed:'.format(dir), ret
        if not end:
            end = 0
        length = length - start - end
        self.thumbs = []
        step = float(length) / (n - 1)
        for i in range(0, n):
            fn = "{0}/{1:0>2}.jpg".format(dir, i)
            ss = int(start + i * step)
            print fn, ss, start + length + end
            cmd = 'ffmpeg -ss {2} -i "{0}" -f image2 -vframes 1 {1} 1>/dev/null 2>&1'.format(filename, fn, ss)
            ret = subprocess.call(cmd, shell=True, close_fds=True)
            if ret != 0:
                print 'ThumbsCreator command {0} failed:'.format(cmd), ret
            self.thumbs.append(fn)

#tc = ThumbsCreator(f, 20, va.duration)
#print tc.thumbs
#exit(0)

class ThumbsJoiner(object):
    def __init__(self, resolution):
        self.dir = '/tmp/thumbs/'
        self.background = '66DD66'
        self.resolution = resolution
    def join(self, cols, rows, va, thumbs):
        imgFile = imageFilenameStr(va.filename)
        cmd = 'convert'
        for i in range(1, rows + 1):
            for j in range(1, cols + 1):
                n = (i - 1) * cols + j - 1
                x_pos = (va.height + 5) * (i - 1)
                y_pos = (va.width + 5) * (j - 1)
                cmd += ' -page +{0}+{1} {2}'.format(y_pos, x_pos, thumbs[n])
        cmd += ' -background "#{0}" -mosaic -bordercolor "#{0}" -border 10x10 -quality 100 {1}'.format(
                self.background, self.dir + imgFile)
        print cmd
        ret = subprocess.call(cmd, shell=True, close_fds=True)
        if ret != 0:
            print 'ThumbsJoiner command {0} failed:'.format(cmd), ret
        for text in (va.audio, va.video, "Size: {0}   Duration: {1}".format(
            filesizeStr(va.filesize), durationStr(va.duration)),
            "Title: {0}".format(titleStr(va.filename))):
            cmd = 'convert {0} -thumbnail {1} -quality 100 -gravity NorthWest   -background "#{2}"  -splice 0x18 -annotate +0+2 "{3}" {0}'.format(
                    self.dir + imgFile, self.resolution, self.background, text)
            ret = subprocess.call(cmd, shell=True, close_fds=True)
            if ret != 0:
                print 'ThumbsJoiner command {0} failed:'.format(cmd), ret
        return self.dir + imgFile

def resolutionStr(cols, rows):
    return str(int(cols) * 256) + 'x' + str(int(rows) * 256)

def consoleMakeThumbs(file, outdir):
    va = VideoAnalizer(file)
    if not va.filename:
        return 1
    rows, cols = rowsCols(va.duration)
    print "Duration: {0} => [{1} x {2}]".format(durationStr(va.duration), cols, rows)
    tc = ThumbsCreator(file, rows * cols, va.duration, 3, 3)
    tj = ThumbsJoiner(resolutionStr(cols, rows))
    imgFile = tj.join(cols, rows, va, tc.thumbs)
    imgFilePath = outdir + '/' + imageFilenameStr(va.filename)
    shutil.copyfile(imgFile, imgFilePath)
    print 'file: {0} => {1}'.format(file, imgFilePath)

class GtkMakeThumbs:
    def addRow(self, cont, items):
        hb = gtk.HBox()
        for i in items:
            hb.pack_start(i)
        cont.pack_start(hb)

    def on_choose_file(self, widget, data = None):
        print "Choose: file:", self.fileChooser.get_filename()
        self.va = VideoAnalizer(self.fileChooser.get_filename())
        print self.va
        self.filename.set_text(self.va.filename)
        self.filesize.set_text(str(self.va.filesize))
        self.dimentions.set_text("{0}x{1}".format(self.va.width, self.va.height))
        self.duration.set_text(durationStr(self.va.duration))
        self.video.set_text(self.va.video)
        self.audio.set_text(self.va.audio)
        self.resolution.set_text(resolutionStr(self.cols.get_text(), self.rows.get_text()))

    def on_step1(self, widget, data=None):
        if not self.fileChooser.get_filename():
            return
        print "Step1: file:", self.fileChooser.get_filename()
        n = int(self.rows.get_text()) * int(self.cols.get_text())
        self.tc = ThumbsCreator(self.fileChooser.get_filename(), n, self.va.duration,
                int(self.startpos.get_text()),
                int(self.endpos.get_text()))
        self.thumbsModel.clear()
        for t in self.tc.thumbs:
            print t
            self.thumbsModel.append([t])
        if len(self.tc.thumbs) > 0:
            self.thumbImg.set_from_file(self.tc.thumbs[0])
        self.nb.next_page()

    def on_step2(self, widget, data=None):
        print "Step2: file:", self.fileChooser.get_filename()
        tj = ThumbsJoiner(self.resolution.get_text())
        self.imgFile = tj.join(int(self.cols.get_text()), int(self.rows.get_text()), self.va, self.tc.thumbs)
        print 'ready file:', self.imgFile
        self.img.set_from_file(self.imgFile)
        self.nb.next_page()

    def on_step3(self, widget, data=None):
        dlg = gtk.FileChooserDialog("Save File...", self.window,
                gtk.FILE_CHOOSER_ACTION_SAVE,
                (gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL,
                    gtk.STOCK_SAVE, gtk.RESPONSE_OK))
        dlg.set_current_folder(os.path.dirname(self.imgFile))
        dlg.set_current_name(os.path.basename(self.imgFile))
        filter = gtk.FileFilter()
        filter.set_name("All files")
        filter.add_pattern("*")
        dlg.add_filter(filter)

        filter = gtk.FileFilter()
        filter.set_name("Images")
        filter.add_mime_type("image/png")
        filter.add_mime_type("image/jpeg")
        filter.add_mime_type("image/gif")
        filter.add_pattern("*.png")
        filter.add_pattern("*.jpg")
        filter.add_pattern("*.gif")
        filter.add_pattern("*.tif")
        filter.add_pattern("*.xpm")
        dlg.add_filter(filter)
        res = dlg.run()
        if res == gtk.RESPONSE_OK:
            print 'saving', dlg.get_filename()
            shutil.copyfile(self.imgFile, dlg.get_filename())
        dlg.destroy()
    def on_choose_thumb(self, tv, path, view_column, user_param1, data=None):
        thumb = self.thumbsModel.get(self.thumbsModel.get_iter(path), 0)[0]
        self.thumbImg.set_from_file(thumb)

    def delete_event(self, widget, event, data=None):
        print "delete event occurred"
        return False

    def destroy(self, widget, data=None):
        print "destroy signal occurred"
        gtk.main_quit()

    def __init__(self):
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.connect("delete_event", self.delete_event)
        self.window.connect("destroy", self.destroy)
        self.window.set_border_width(10)

        self.nb = gtk.Notebook()
        # step 1
        self.step1 = gtk.Button("Next")
        self.step1.connect("clicked", self.on_step1, None)
        self.fileChooser = gtk.FileChooserButton('Select a File')
        self.fileChooser.set_current_folder('/mnt/sandbox/tmpfiles/tmp/done')
        self.fileChooser.connect("file-set", self.on_choose_file, None)

        self.rows = gtk.Entry()
        self.rows.set_text('5')
        self.cols = gtk.Entry()
        self.cols.set_text('4')
        self.startpos = gtk.Entry()
        self.startpos.set_text('3')
        self.endpos = gtk.Entry()
        self.endpos.set_text('3')
        self.resolution = gtk.Entry()
        self.resolution.set_text(str(int(self.cols.get_text()) * 256) + 'x' + str(int(self.rows.get_text()) * 256))
        self.filename = gtk.Label()
        self.dimentions = gtk.Label()
        self.filesize = gtk.Label()
        self.duration = gtk.Label()
        self.video = gtk.Label()
        self.audio = gtk.Label()

        vb = gtk.VBox()
        self.addRow(vb, [gtk.Label('Rows:'), self.rows, gtk.Label('Cols:'), self.cols])
        self.addRow(vb, [gtk.Label('Start:'), self.startpos, gtk.Label('End:'), self.endpos])
        vb.pack_start(self.fileChooser)
        self.addRow(vb, [gtk.Label('Resolution:'), self.resolution])
        self.addRow(vb, [self.filename])
        self.addRow(vb, [self.filesize, self.dimentions, self.duration])
        self.addRow(vb, [self.video])
        self.addRow(vb, [self.audio])
        vb.pack_start(self.step1, expand=False)
        self.nb.append_page(vb, gtk.Label('Choose file'))

        # step 2
        self.step2 = gtk.Button("Next")
        self.step2.connect("clicked", self.on_step2, None)
        self.thumbsModel = gtk.ListStore(gobject.TYPE_STRING)
        self.thumbs = gtk.TreeView(self.thumbsModel)
        swTh = gtk.ScrolledWindow()
        swTh.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
        swTh.add(self.thumbs)

        self.thumbs.connect("row-activated", self.on_choose_thumb, None)
        textrenderer = gtk.CellRendererText()
        col = gtk.TreeViewColumn('Image', textrenderer, text=0)
        self.thumbs.append_column(col)
        self.thumbImg = gtk.Image()
        swIm = gtk.ScrolledWindow()
        swIm.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
        swIm.add_with_viewport(self.thumbImg)

        hb = gtk.HBox()
        hb.pack_start(swTh, expand=False)
        hb.pack_start(swIm, expand=True)

        vb = gtk.VBox()
        vb.pack_start(hb)
        vb.pack_start(self.step2, expand=False)
        self.nb.append_page(vb, gtk.Label('Check thumbs'))

        # step 3
        self.step3 = gtk.Button("Save image")
        self.step3.connect("clicked", self.on_step3, None)
        self.img = gtk.Image()
        swIm = gtk.ScrolledWindow()
        swIm.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
        swIm.add_with_viewport(self.img)

        vb = gtk.VBox()
        vb.pack_start(swIm)
        vb.pack_start(self.step3, expand=False)
        self.nb.append_page(vb, gtk.Label('Save image'))

        self.window.add(self.nb)
        self.nb.show_all()
        self.window.show()

    def main(self):
        gtk.main()

import pygtk
pygtk.require('2.0')
import gtk, gobject

def main(argv=None):
    if argv is None:
        argv = sys.argv
    file, outdir = None, None
    try:
        opts, args = getopt.getopt(argv[1:], "", ["file=", "outdir="])
    except getopt.GetoptError, err:
        print str(err)
        return 1
    for k, v in opts:
        if k == '--file':
            file = v
        elif k == '--outdir':
            outdir = v
    if file:
        if not outdir:
            outdir = os.path.dirname(file)
        return consoleMakeThumbs(file, outdir)
    else:
        w = GtkMakeThumbs()
        w.main()

if __name__ == "__main__":
    sys.exit(main())

