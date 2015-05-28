import java.io.*;
import java.util.*;

public class Main{

	static ArrayList<ArrayList<Edge>> list;
	static Edge[][] matrix;
	static int start, finish;

	static int findFlow(){
		int[] height = new int[list.size()];
		Arrays.fill(height, -1);
		Queue<Integer> queue = new ArrayDeque<Integer>();
		height[start] = 0;
		queue.add(start);
		while(!queue.isEmpty()){
			int now = queue.poll();
			for(Edge e : list.get(now)){
				int next = e.v;
				if(e.cap == 0) continue;
				if(height[next] != -1) continue;
				height[next] = height[now]+1;
				queue.add(next);
			}
		}
		if(height[finish] == -1) return 0;
		int result = 0, flow;
		while((flow = trace(start, Integer.MAX_VALUE, height)) != 0) result += flow;
		return result;
	}

	static int trace(int now, int flow, int[] height){
		if(now == finish){
			return flow;
		}
		int result = 0;
		for(Edge e : list.get(now)){
			if(e.cap == 0) continue;
			int next = e.v;
			if(height[now]+1 != height[next]) continue;
			result = trace(next, Math.min(flow, e.cap), height);
			if(result != 0){
				matrix[now][next].cap -= result;
				matrix[next][now].cap += result;
				break;
			}
		}
		return result;
	}

	static class Edge{
		int u, v, cap;

		public Edge(int u, int v, int cap, Edge[][] matrix){
			this.u = u;
			this.v = v;
			this.cap = cap;
			matrix[u][v] = this;
		}
	}

}