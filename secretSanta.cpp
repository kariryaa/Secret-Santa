#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<int> cycle;
// int ct = 0;
int myrandom (int i) { return rand()%i;}

bool dfs(vector< vector<bool> > arr, vector<bool> vis, int n, int start)
{
    int len = arr.size();
    bool flag = false;
    for(int i=0;i<len && !flag;i++)
    {
        flag = flag|vis[i];
    }
    if(!flag)
    {
        if(arr[n][start])
        {	
        	// ct++;
        	cycle.push_back(n);
        	return true;
        }
       	return false;
    }
    for(int i=0;i<len;i++)
    {
        if(vis[i] && arr[n][i])
        {
            //cout<<n<<"\t"<<i<<endl;
            vis[i] = false;
            flag = dfs(arr, vis, i, start);
            if(flag)
            {
            	// ct++;
            	cycle.push_back(n);
            	return true;
            }
            vis[i] = true;
        }
    }
    return false;
}

bool hamil(vector< vector<bool> > arr)
{
    int len = arr.size();
    vector<bool> vis(len, true);
    vis[0]=false;
    
    // for(int i=0;i<len;i++)
    // {
    //     //cout<<"starting hamil from: "<<i<<endl;
    vis[0]=false;
    if(dfs(arr, vis, 0, 0))
        return true;
        // vis[i]=true;
    // }
    return false;
}

int main()
{
	srand ( unsigned ( std::time(0) ) );
	fstream fin("input.txt");
	fstream fb("blacklist.txt");
	fstream fout("output.txt");

	vector<string> names;
	unordered_map<string, string> map;
	while(!fin.eof())
	{
		string name;
		fin>>name;
		names.push_back(name);
		string id;
		fin>>id;
		map[name] = id;
	}
	int len = names.size();
	random_shuffle(names.begin(), names.end(), myrandom);

	vector< vector<bool> > graph;
	vector< vector<bool> > vis;
	for(int i=0;i<len;i++)
	{
		vector<bool> row;
		for(int j=0;j<len;j++)
		{
			row.push_back(true);
		}
		graph.push_back(row);
		vis.push_back(row);
	}
	for(int i=0;i<len;i++)
		graph[i][i] = false;

	while(!fb.eof())
	{
		string n1,n2;
		fb>>n1;
		fb>>n2;
		graph[distance(names.begin(), find(names.begin(), names.end(), n1))][distance(names.begin(), find(names.begin(), names.end(), n2))] = false;
	}

	hamil(graph);
	// cout<<ct;
	cout<<"\n";
	//cout<<setw(10);
	for(int i=0;i<cycle.size()-1;i++)
	{
		cout<<names[cycle[i]];
		cout<<"\t-->\t";
		cout<<names[cycle[i+1]]<<endl;
	}
	cout<<names[cycle[cycle.size()-1]];
	cout<<"\t-->\t";
	cout<<names[cycle[0]]<<endl;

	return 0;
}