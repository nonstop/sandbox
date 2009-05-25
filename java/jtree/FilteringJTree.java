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


public class FilteringJTree extends JPanel {
    private JTree tree;

    public FilteringJTree(DefaultMutableTreeNode top) {
        super(new GridLayout(1,0));
        tree = new JTree(top);
        add(tree);
    }
    public TreeSelectionModel getSelectionModel() {
        return tree.getSelectionModel();
    }
}
