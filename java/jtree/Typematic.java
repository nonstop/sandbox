// Confidential & Proprietary Information
// Copyright 2002 Ontology Works, Inc. All rights reserved.

import javax.swing.KeyStroke;
import javax.swing.JComponent;
import javax.swing.JList;
import javax.swing.JTree;
import javax.swing.ListModel;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * A Typematic enables fast traversal of lists of items in certain kinds of
 * JComponents, by allowing the user to type in the first few characters of
 * the desired item.
 *
 * <p> Typematic is an ActionListener, but it isn't used by adding it to a
 * component; rather, it is constructed and passed the desired component,
 * and it will take care of the rest.
 *
 * <p> A time limit can be set denoting when a keystroke sequence is
 * considered expired.  Any subsequent keystrokes are treated as the
 * beginning of a new sequence.  The default time limit is one second.
 *
 * <p> The keyboard traversal algorithm is similar to that used in Windows
 * 98 Explorer windows.  When a sequence is typed, the items in the
 * JComponent are searched, starting with the one below the currently
 * selected item and working down, wrapping around to the top.  The first
 * item found beginning with the sequence becomes the new selected item.
 * As the sequence is typed, the item selected may change, if it no longer
 * fully matches the sequence in progress.  If a particular character is
 * repeated, the algorithm instead traverses cyclically those items whose
 * first character is a match.
 *
 * <p> Typematic pays attention only to ASCII character codes 32 through
 * 126 inclusive.  Case is ignored.  Only JLists and JTrees are supported,
 * provided they are in single selection mode.  If a Typematic is assigned
 * to anything else, nothing interesting happens; if assigned to a JList or
 * JTree in multiple selection mode, the results are undefined.
 *
 * @author	Paul Brinkley (brinkley@knowledgebus.com)
 * @version	1.00 19990921
 */
public class Typematic implements ActionListener
{
  // Class constants ------------------------------------------------------
  /** Keystroke sequence expiration time limit in milliseconds. */
  private static int defaultExpire = 1000;

  private static String[] commands;

  // Inclusive range of ASCII char codes employed in a Typematic
  private static final int minCode = 32;
  private static final int maxCode = 126;

  static {
    commands = new String[maxCode-minCode+1];
    char[] c = new char[1];
    for (int i = minCode; i <= maxCode; i++) {
      c[0] = (char) i;
      commands[i-minCode] = new String(c).toLowerCase();
    }
  }

  // Instance variables ---------------------------------------------------
  int expire;
  long lastTime;
  boolean firstChar;
  String currentSeq;
  JComponent component;

  // Constructor ----------------------------------------------------------

  /** Constructs a new Typematic for the given JComponent, with the default
   * expiration. */
  public Typematic (JComponent comp)
  {
    this (comp, defaultExpire);
  }

  /** Constructs a new Typematic for the given JComponent, with the given
   * expiration time in milliseconds.  If the expiration time elapses
   * between two typed characters, the latter is considered to be the start
   * of a new character sequence.
   */
  public Typematic (JComponent comp, int millis)
  {
    for (int i = minCode; i <= maxCode; i++) {
      char c = (char) i;
      String command = commands[i-minCode];
      comp.registerKeyboardAction (this, command,
        KeyStroke.getKeyStroke (c), JComponent.WHEN_FOCUSED);
    }
    component = comp;
    expire = millis;
    lastTime = 0;
    firstChar = true;
    currentSeq = new String();
  }

  // Default expire time --------------------------------------------------

  /** Returns the default expiration time for Typematics. */
  public static int getDefaultExpire() { return defaultExpire; }

  /** Sets the default expiration time for Typematics.  Any new Typematics
   * will use the new default expiration time unless set otherwise.  Any
   * existing Typematics will be unaffected.
   */
  public static void setDefaultExpire(int expire)
  { defaultExpire = expire; }

  // Event handler --------------------------------------------------------

  public void actionPerformed (ActionEvent e)
  {
    processChar (e.getActionCommand().charAt(0));
  }

  private void processChar (char c)
  {
    long timeNow = System.currentTimeMillis();
    int timeSince = (int) (timeNow - lastTime);
    lastTime = timeNow;
    if ((timeSince >= expire) || firstChar)
      startNewSeq (c);
    else
      continueSeq (c);
    firstChar = false;
  }

  private void startNewSeq (char c)
  {
    char[] ca = new char[] { c };
    currentSeq = new String(ca);
    searchForMatch();
  }

  // To decide whether to cycle on the first char:
  // Cycle iff currentSeq's last char matches the char just passed,
  //  and if appending the new char onto currentSeq would break the
  //  current match.

  private void continueSeq (char c)
  {
    if (getCurrentIndex() == -1) return;
    String newSeq = currentSeq + c;
    if (getItemString(getCurrentIndex()).startsWith(newSeq))
      currentSeq = newSeq;
    else {
      if ((currentSeq.length() == 0) ||
          (currentSeq.charAt(currentSeq.length()-1) == c))
        startNewSeq (c);
      else {
        currentSeq = newSeq;
        searchForMatch();
      }
    }
  }

  private void searchForMatch()
  {
    int lastIdx = getLastIndex();
    if (lastIdx == -1) return;

    // Now we know the component has at least one selectable item.
    int idx = getCurrentIndex()+1;
    if (idx > lastIdx) idx = 0;
    int stopIdx = idx;
    boolean matched = false;

    do {
      matched = getItemString(idx).startsWith(currentSeq);
      if (!matched) {
        idx++;
        if (idx > lastIdx) idx = 0;
      }
    }
    while ((idx != stopIdx) && (!matched));

    if (matched)
      setSelectedIndex(idx);
  }

  private int getCurrentIndex()
  {
    int retval = -1;
    if (component instanceof JList)
      retval = ((JList) component).getSelectedIndex();
    else if (component instanceof JTree) {
      int[] rows = ((JTree) component).getSelectionRows();
      retval = (rows == null) ? -1 : rows[0];
    }
    return retval;
  }

  private int getLastIndex()
  {
    int retval = -1;
    if (component instanceof JList) {
      ListModel model = ((JList) component).getModel();
      retval = model.getSize() - 1;
    }
    else if (component instanceof JTree)
      retval = ((JTree) component).getRowCount() - 1;
    return retval;
  }

  private String getItemString(int idx)
  {
    Object item = null;
    if (component instanceof JList) {
      ListModel model = ((JList) component).getModel();
      item = model.getElementAt(idx);
    }
    else if (component instanceof JTree) {
      JTree tree = (JTree) component;
      item = tree.getPathForRow(idx).getLastPathComponent();
    }
    String retval = null;
    if (item != null)
      retval = item.toString().toLowerCase();
    return retval;
  }

  private void setSelectedIndex(int idx)
  {
    if (component instanceof JList) {
      JList list = (JList) component;
      list.setSelectedIndex(idx);
      list.ensureIndexIsVisible(idx);
    }
    else if (component instanceof JTree)
    {
      JTree tree = (JTree) component;
      tree.setSelectionRow(idx);
      tree.scrollRowToVisible(idx);
    }
  }
}

