/* Time Complexity=2*n*log(n)*log(n) */
#include <cstdio>
#include <algorithm>
using namespace std;

class Weight{
public:
    Weight(int a=0,int b=0,int c=0):id(a),first(b),second(c){}
    int id,first,second;
    bool operator<(const Weight &rhs)const{
        return first<rhs.first||(first==rhs.first&&second<rhs.second);
    }
    bool operator==(const Weight &rhs)const{
        return first==rhs.first&&second==rhs.second;
    }
    bool operator!=(const Weight &rhs)const{
        return!((*this)==rhs);
    }
};

class SuffixArray{
public:
    SuffixArray(char *r):refer(r){
        for(length=0;refer[length]!='\0';length++);
        rankOfIndex=new int[length];
        indexOfRank=new int[length];
        texi=new Weight[length];//=
        firstsort();
        for(int know=1;know<=length;know<<=1) doublesort(know);
    }
    ~SuffixArray() {
        delete [] rankOfIndex;
        delete [] indexOfRank;
        delete [] texi;
    }

    void firstsort(){
        for(int i=0;i<length;i++){
            texi[i]=Weight(i,refer[i]);
        }
        sort(&texi[0],&texi[length-1]+1);

        indexOfRank[rankOfIndex[texi[0].id]=0]=texi[0].id;
        int current=0;
        for(int i=1;i<length;i++){
            if(texi[i]!=texi[i-1]) current++;
            indexOfRank[i]=texi[i].id;
            rankOfIndex[texi[i].id]=current;
        }
    }

    void doublesort(int known){
        for(int i=0;i<length;i++){
            texi[i]=Weight(i,rankOfIndex[i],(i+known<length)?rankOfIndex[i+known]:-1);
        }

        sort(&texi[0],&texi[length-1]+1);

        indexOfRank[rankOfIndex[texi[0].id]=0]=texi[0].id;
        int current=0;
        for(int i=1;i<length;i++){
            if(texi[i]!=texi[i-1]) current++;
            indexOfRank[i]=texi[i].id;
            rankOfIndex[texi[i].id]=current;
        }

    }

    void print(int i,bool newline=0){
        printf("%s",&refer[indexOfRank[i]]);
        if(newline) printf("\n");
    }

    void printall(){
        for(int i=0;i<length;i++) print(i,1);
    }

    int *indexOfRank,*rankOfIndex,length;
    char *refer;
    Weight *texi;
};

int main()
{
    char str[100];
    scanf("%s", str);
    SuffixArray a(str);
    a.printall();
    return 0;
}
