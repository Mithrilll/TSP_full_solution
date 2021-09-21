#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>

int sum(std::vector<int> vec, std::vector<std::vector<int>> G)
{
	int s = 0;

	for (int i = 0; i < vec.size() - 1; i++)
		s += G[vec[i]][vec[i + 1]];
	s += G[vec[G.size() - 1]][vec[0]];

	return s;
}

std::vector<int> TSP(std::vector<std::vector<int>> G, int start)
{
	std::vector<int> curr;
	std::vector<int> ans;

	int sum_curr = 0;
	int sum_ans = 0;

	curr.push_back(start);

	for (int i = 0; i < G.size(); i++)
	{
		if(i != start)
			curr.push_back(i);
	}

	ans = curr;

	sum_curr = sum(curr, G);

	sum_ans = sum_curr;


	/*for (int i = 0; i < curr.size() - 1; i++)
		std::cout << curr[i] << "->";
	std::cout << curr[curr.size() - 1] << "->" << curr[0] <<" : " << sum_curr << std::endl;*/

	sum_ans = sum_curr;

	int i = G.size()-2;
	int j = G.size()-1;

	while (1)
	{
		while (i > 0 && curr[i] > curr[i + 1])
			i--;

		if (i == 0)
			break;

		while (curr[j] < curr[i] && j > i)
			j--;

		std::swap(curr[i], curr[j]);

		//std::sort(curr[i+1], curr[G.size()-1]);
		for (int k = i + 1; k < curr.size(); k++)
			for (int l = i + 1; l < curr.size() - k + i; l++)
				if (curr[l] > curr[l + 1])
					std::swap(curr[l], curr[l + 1]);

		sum_curr = sum(curr, G);

		if (sum_curr <= sum_ans)
		{
			sum_ans = sum_curr;
			ans = curr;
		}

		/*for (int i = 0; i < curr.size() - 1; i++)
			std::cout << curr[i] << "->";
		std::cout << curr[curr.size() - 1] << "->" << curr[0] << " : " << sum_curr << std::endl;*/

		i = G.size() - 2;
		j = G.size() - 1;
	}


	return ans;
}

int main()
{
	int n;
	int s;
	std::cin >> n;

	srand(time(0));

	std::vector<std::vector<int>> Mat(n);
	for(int i =0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				Mat[i].push_back(0);
			else
				Mat[i].push_back(rand() % 9 + 1);
		}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			std::cout << Mat[i][j] << " ";
		std::cout << std::endl;
	}

	std::cin >> s;
	std::vector<int> sol = TSP(Mat, s);

	for (int i = 0; i < sol.size() - 1; i++)
		std::cout << sol[i] << "->";
	std::cout << sol[sol.size()-1] << "->" << sol[0] << " : " << sum(sol, Mat) << std::endl;


	return 0;
}