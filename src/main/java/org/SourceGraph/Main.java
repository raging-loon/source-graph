package org.SourceGraph;

import org.SourceGraph.Graph.Graph;
import org.SourceGraph.Interface.GraphViewPanel;

import javax.swing.*;

public class Main {
    public static void main(String[] args) {
        Graph test = new Graph();
        test.addNode("test.h", "test2.h");
        test.addNode("test.h", "test3.h");
        test.addNode("test3.h", "test4.h");
        test.addNode("test4.h", "test5.h");
        JFrame frame = new JFrame("Graph Visualization");
        GraphViewPanel graphPanel = new GraphViewPanel(test, "test.h");
        frame.add(graphPanel);
        frame.setSize(400, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}