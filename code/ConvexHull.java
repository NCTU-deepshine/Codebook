import java.io.*;
import java.util.*;

public class Main{

	public static void main(String[] args){
		Scan scan = new Scan();
		int testcases = scan.nextInt();
		while(testcases-- != 0){
			int n = scan.nextInt();
			Coordinate[] vertex = new Coordinate[n];
			for(int i=0;i<n;i++) vertex[i] = new Coordinate(scan.nextDouble(), scan.nextDouble());
			Arrays.sort(vertex);
//			for(Coordinate c : vertex){
//				System.out.println(c.x+" "+c.y);
//			}
			Coordinate[] list = new Coordinate[n+1];
			int index = 0;
			for(int i=0;i<n;i++){
				while(index >= 2 && ABcrossAC(list[index-2], list[index-1], vertex[i]) <= 0) index--;
				list[index++] = vertex[i];
			}
			int half_point = index+1;
			for(int i=n-2;i>=0;i--){
				while(index >= half_point && ABcrossAC(list[index-2], list[index-1], vertex[i]) <= 0) index--;
				list[index++] = vertex[i];
			}
			double result = 0.0;
			//System.out.println(list[0].x+" "+list[0].y);
			for(int i=1;i<index;i++){
				//System.out.println(list[i].x+" "+list[i].y);
				result += Math.sqrt((list[i].x-list[i-1].x)*(list[i].x-list[i-1].x) + (list[i].y-list[i-1].y)*(list[i].y-list[i-1].y));
			}
			System.out.println(result);
		}
	}

	static double ABcrossAC(Coordinate A, Coordinate B, Coordinate C){
		return (B.x-A.x) * (C.x-A.x) - (B.y-A.y) * (C.y-A.y);
	}

	static class Coordinate implements Comparable<Coordinate>{

		double x,y;

		Coordinate(double x, double y){
			this.x = x;
			this.y = y;
		}

		@Override
		public int compareTo(Coordinate o){
			if(x < o.x) return -1;
			if(x > o.x) return 1;
			if(y < o.y) return -1;
			if(y > o.y) return 1;
			return 0;
		}

	}


}

class Scan implements Iterator<String>{

	BufferedReader buffer;
	StringTokenizer tok;

	Scan(){
		buffer = new BufferedReader(new InputStreamReader(System.in));
	}


	@Override
	public boolean hasNext(){
		while(tok == null || !tok.hasMoreElements()){
			try{
				tok = new StringTokenizer(buffer.readLine());
			}catch(Exception e){
				return false;
			}
		}
		return true;
	}

	@Override
	public String next(){
		if(hasNext()) return tok.nextToken();
		return null;
	}

	@Override
	public void remove(){
		throw new UnsupportedOperationException();
	}

	int nextInt(){
		return Integer.parseInt(next());
	}

	long nextLong(){
		return Long.parseLong(next());
	}

	double nextDouble(){
		return Double.parseDouble(next());
	}

	String nextLine(){
		if(hasNext()) return tok.nextToken("\n");
		return null;
	}
}