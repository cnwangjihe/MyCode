#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

char hzc[100];

int main(){
	int task_id;
	scanf("%d",&task_id);
	
	sprintf(hzc,"tsp%d.in",task_id);
	freopen(hzc,"r",stdin);
	
	scanf("%d",&n);
	for (int a=1;a<=n;a++)
		scanf("%d%d",&x[a],&y[a]);
		
	for (int a=1;a<=n;a++)
	{
		now_solution[a] = a;
		final_solution[a] = a;
	}
	nowcost = getcost(now_solution);
	finalcost = getcost(final_solution);
	
	for (;;) {
		random_shuffle(now_solution+2,now_solution+n+1);
		nowcost = getcost(now_solution);
		if (nowcost < finalcost) {
			finalcost = nowcost;
			final_solution = now_solution;
			sprintf(hzc,"D:\\TEST\\tsp%d.out",task_id);
			freopen(hzc,"w",stdout);
			printf("%array",final_solution);
			fclose(stdout);
		}
	}
	
	
	return 0;
}



void simulate_fire()
{
	double T=10000;
	double alpha = 0.99;
	int times = 100;
	while (T > 1e-3) {
		for (int a=1;a<=times;a++)
		{
			new_solution = generate_solution(now_solution);
			new_cost = get_cost(new_solution);
			double p = (double)rand()/RAND_MAX;
			if (new_cost > now_cost || p <= exp((new_cost-now_cost)/T)) {
				now_solution = new_solution;
				now_cost = new_cost;
				if (now_cost > final_cost) {
					final_solution = now_solution;
					final_cost = now_cost;
				}
			}
		}
		T = T * alpha;
	}
}


