import java.util.*;

class MyHashMap{

	int MAX;
	int[] table;
	boolean[] selecter;
	long[] values;

	MyHashMap(){
		MAX = 16;
		table = new int[1<<MAX];
		Arrays.fill(table, -1);
		selecter = new boolean[1<<MAX];
		values = new long[1<<MAX];
	}

	MyHashMap(int capacity){
		MAX = capacity;
		table = new int[1<<MAX];
		Arrays.fill(table, -1);
		selecter = new boolean[1<<MAX];
		values = new long[1<<MAX];
	}

	void put(int key, long value){

		int hash, activeKey = key, nextKey;
		boolean activeSelect = true, nextSelect;
		long activeValue = value, nextValue;

		hash = hashing1(key);
		if(table[hash] == key){
			values[hash] = value;
			return;
		}
		hash = hashing2(key);
		if(table[hash] == key){
			values[hash] = value;
			return;
		}

		do{
			hash = activeSelect ? hashing1(activeKey) : hashing2(activeKey);
			nextKey = table[hash];
			nextSelect = selecter[hash];
			nextValue = values[hash];
			table[hash] = activeKey;
			selecter[hash] = !activeSelect;
			values[hash] = activeValue;
			activeKey = nextKey;
			activeSelect = nextSelect;
			activeValue = nextValue;
			if(activeKey==key && activeSelect) break;
		}while(activeKey != -1);

		if(activeKey == key){
			expand();
			put(key, value);
		}
	}

	long get(int key){
		int hash = hashing1(key);
		if(table[hash] == key) return values[hash];
		hash = hashing2(key);
		if(table[hash] == key) return values[hash];
		put(key, 0l);
		return 0l;
	}

	boolean remove(int key){
		int hash = hashing1(key);
		if(table[hash] == key){
			table[hash] = -1;
			return true;
		}
		hash = hashing2(key);
		if(table[hash] == key){
			table[hash] = -1;
			return true;
		}
		return false;
	}

	int hashing1(int x){
		x = (x+0x7ed55d16) + (x<<12);
		x = (x^0xc761c23c) ^ (x>>19);
		x = (x+0x165667b1) + (x<<5);
		x = (x+0xd3a2646c) ^ (x<<9);
		x = (x+0xfd7046c5) + (x<<3);
		x = (x^0xb55a4f09) ^ (x>>16);
		return x & 0x7fffffff>>(32-MAX);
	}

	int hashing2(int x){
		x -= (x<<6);
		x ^= (x>>17);
		x -= (x<<9);
		x ^= (x<<4);
		x -= (x<<3);
		x ^= (x<<10);
		x ^= (x>>15);
		return x & 0x7fffffff>>(32-MAX);
	}

	void expand(){
		MAX++;
		int[] oldTable = table;
		long[] oldValues = values;
		table = new int[1<<MAX];
		Arrays.fill(table, -1);
		selecter = new boolean[1<<MAX];
		values = new long[1<<MAX];
		for(int i = 0;i<oldTable.length;i++){
			if(oldTable[i] == -1) continue;
			put(oldTable[i], oldValues[i]);
		}
	}

}