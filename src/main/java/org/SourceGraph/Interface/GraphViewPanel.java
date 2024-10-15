package org.SourceGraph.Interface;

import org.SourceGraph.Graph.Graph;

import javax.swing.*;
import java.awt.*;
import java.util.List;

public class GraphViewPanel  extends JPanel {
    Graph mGraph;
    String mTarget;
    public GraphViewPanel(Graph g, String target) {
        mGraph = g;
        mTarget = target;
    }

    @Override
    protected void paintComponent(Graphics g) {
        List<Integer> neighbors = mGraph.getAdjacencyList().get(mGraph.getIndexFromName(mTarget));
        if(neighbors == null)
            return;

        int startX = 300;
        int startY = 300;
        paintNode(g, mTarget, startX, startY);
        int locx = startX + 100;
        int locy = startY;
        for(Integer i : neighbors) {
            locy += 100;
            g.drawLine(startX, startY, locx, locy);
            paintNode(g,mGraph.getNameFromIndex(i.intValue()), locx, locy);
        }
    }


    private void paintNode(Graphics g, String str, int x, int y)
    {
        g.setColor(Color.WHITE);
        g.fillOval(x - 15, y - 15, 30, 30);
        g.setColor(Color.BLACK);
        g.drawString(str, x - 10, y + 5);
    }
}

