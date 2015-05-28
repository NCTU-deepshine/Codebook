public class Main{

	static int[] zAlgorithm(char[] s){
		int[] z = new int[s.length];
		z[0] = s.length;
		int l = -1, r = -1;
		for(int i=1;i<s.length;i++){
			if(s[0] != s[i]){
				z[i] = 0;
				continue;
			}
			if(r < i){
				l = i;
				int j;
				for(j=1;l+j<s.length;j++){
					if(s[j] != s[l+j]) break;
				}
				r = l+j-1;
				z[i] = j;
			}else{
				int pre = i-l, post = r-i+1;
				if(z[pre] < post){
					z[i] = z[pre];
				}else{
					z[i] = post;
					l = i;
					int j;
					for(j=0;r+1+j<s.length;j++){
						if(s[r+1+j-l] != s[r+1+j]) break;
					}
					r = r+j;
					z[i] += j;
				}
			}
		}
		return z;
	}
}