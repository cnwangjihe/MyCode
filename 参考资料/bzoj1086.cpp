int nodes[];
int cc;

int dfs(int x)
{
	int tot=0;
	int son;
	while(һ���µ�son)
	{
		tot+=dfs(son);
		if(tot>=B)
		{
			int i;
			for(i=1;i<=tot;i++)
			{
				nodes[cc]����һ���
				cc--; 
			}
			tot=0;
		}
	}
	cc++;
	nodes[cc]=x;
	return tot+1;
}
