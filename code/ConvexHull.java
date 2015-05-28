static int convexHull(Coordinate[] vertex, Coordinate[] list){
		int n = vertex.length;
		Arrays.sort(vertex);
		int index = 0;
		for(int i=0;i<n;i++){
		while(index >= 2 && ABcrossAC(list[index-2], list[index-1], vertex[i]) <= 0) index--;
		list[index++] = vertex[i];
		}
		int half_point = index+1;
		for(int i=n-2;i>=0;i--){
		while(index>=half_point && ABcrossAC(list[index-2], list[index-1], vertex[i])<=0) index--;
		list[index++] = vertex[i];
		}
		return index;
		}

static double ABcrossAC(Coordinate A, Coordinate B, Coordinate C){
		return (B.x-A.x) * (C.y-A.y) - (B.y-A.y) * (C.x-A.x);
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