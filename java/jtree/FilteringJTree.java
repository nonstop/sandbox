import javax.swing.KeyStroke;
import javax.swing.JComponent;
import javax.swing.JEditorPane;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.UIManager;

import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeSelectionModel;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;

import java.net.URL;
import java.io.IOException;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;


public class FilteringJTree extends JPanel implements ActionListener {
    private JTree tree;
    private JPanel filterPanel;

    public FilteringJTree(DefaultMutableTreeNode top) {
        super(new GridLayout(1,0));
        tree = new JTree(top);
        tree.setPreferredSize(new Dimension(500, 200));

        tree.registerKeyboardAction(this, KeyStroke.getKeyStroke('/'), JComponent.WHEN_FOCUSED);
        tree.registerKeyboardAction(this, KeyStroke.getKeyStroke('a'), JComponent.WHEN_FOCUSED);
        tree.registerKeyboardAction(this, KeyStroke.getKeyStroke('b'), JComponent.WHEN_FOCUSED);

        filterPanel = new JPanel();
        filterPanel.setVisible(false);
        JSplitPane splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, tree, filterPanel);
        splitPane.setPreferredSize(new Dimension(500, 300));

        add(splitPane);
    }
    public TreeSelectionModel getSelectionModel() {
        return tree.getSelectionModel();
    }

    // Event handler --------------------------------------------------------
    public void actionPerformed (ActionEvent e)
    {
        filterPanel.setVisible(!filterPanel.isVisible());
    }
}
