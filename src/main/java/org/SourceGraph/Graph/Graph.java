package org.SourceGraph.Graph;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Graph {
    ArrayList<String> mNodes = new ArrayList<>();
    Map<Integer, List<Integer>> mAdjList = new HashMap<>();

    public Graph() {}

    public void addNode(String from, String to) {
        addSingleNode(from);
        addSingleNode(to);

        int fromidx = mNodes.indexOf(from);
        int toidx = mNodes.indexOf(to);
        List<Integer> fromList  = mAdjList.get(fromidx);
        if(!fromList.contains(toidx))
            fromList.add(toidx);
    }

    private void addSingleNode(String name) {
        if(!mNodes.contains(name))
        {
            mAdjList.put(mNodes.size(), new ArrayList<>());
            mNodes.add(name);

        }
    }

    public final Map<Integer, List<Integer>> getAdjacencyList() { return mAdjList; }
    public String getNameFromIndex(int idx) {
        return mNodes.get(idx);
    }
    public int getIndexFromName(String name) {
        return mNodes.indexOf(name);
    }
}
