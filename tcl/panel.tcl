#!/bin/sh
# the next line restarts using wish \
exec wish8.4 "$0" "$@"

set menu { {
{#ffffff} xterm    xterm
{#8888ff} mc       {xterm -e mc}
} {
{#ffff00} gimp     gimp
{#999999} xmms     xmms
} {
{#9999ff} FF       firefox
{#9999ff} mail     thunderbird
} }

set font {-*-verdana-bold-r-*-*-9-*-*-*-*-*-*-r}

proc next_time_step {} {
  global time
  set time [clock format [clock seconds] -format {%H:%M}]
  after 1000 next_time_step
}

proc hide_all {} {
  global bottons
  foreach {n p} [eval concat $bottons] { grid forget $n }
}

proc show_panel {btn} {
  global bottons
  foreach {n p} [lindex $bottons $btn] {
    grid $n -column $p -row 0 -sticky news
  }
}

proc click {b} {
  raise .
  hide_all
  show_panel $b
}

proc execute {cmd} {
  if {[catch "exec $cmd {&}" err]} {
    tk_messageBox -default ok -icon error -message $err \
                  -title error -type ok
  }
}

proc menu2bottons {menu} {
  global font
  set bottons {}
  set c 0
  foreach {m} $menu {
    set i 1
    set b {}
    foreach {clr lab cmd} $m {
      set n [label .u$c -text $lab -fg $clr -bg {#000000} -font $font \
            -padx 2 -pady 0 -anchor w -borderwidth 1 -relief raised]
      bind $n <Button-1> [list execute $cmd]
      lappend b $n $i
      incr i
      incr c
    }
    lappend bottons $b
  }
  return $bottons
}

set bottons [menu2bottons $menu]
set time {00:00}
set n [label .l -textvariable time -fg {#999999} -bg #000000 -font $font \
      -padx 2 -pady 0 -anchor w -borderwidth 1 -relief raised]
bind $n <Button-1> {click 0}
bind $n <Button-2> {click 1}
bind $n <Button-3> {click 2}
grid $n -sticky news -column 0 -row 0
bind . <Control-q> {exit}
bind . <FocusOut> {hide_all}
wm title . {ctrl-panel}
wm transient .
wm resizable . 0 0
next_time_step

