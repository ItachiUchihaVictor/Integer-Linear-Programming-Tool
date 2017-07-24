#include <cstdio>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include "sys/types.h"
#include "sys/wait.h"
#include "sys/times.h"
#include "sys/resource.h"
int parseLine(char* line){
        // This assumes that a digit will be found and the line ends in " Kb".
        int i = strlen(line);
        const char* p = line;
        while (*p <'0' || *p > '9') p++;
        line[i-3] = '\0';
        i = atoi(p);
        return i;
}
int getSpace(){ //Note: this value is in KB!
        FILE* file = fopen("/proc/self/status", "r");
        int result = -1;
        char line[128];

        while (fgets(line, 128, file) != NULL){
            if (strncmp(line, "VmPeak:", 7) == 0){
                 result = parseLine(line);
                 break;
               }
        }
        fclose(file);
        return result/(1024);
}

int main(int argc, char *argv[])
{
    std::cout << "hello" <<std::endl;
//    std::cout << "england.nodes";
    char configFile[255]="config.txt";
    char oFile[255] = "small_o2.txt";
    char pFile[255] = "small_p2.txt";
    char fFile[255] = "small_p2.txt";
    char modFile[255] = "model.mod";
//    char outfilename_o[255] = "match_o.txt";
//    char outfilename_p[255] = "match_p.txt";
//    char outfilename_c[255] = "match_c.txt";
//    char outfilename_d[255] = "match_d.txt";
//    char outfilename_cost[255] = "match_cost.txt";
    
//    char outfilename_profit[255] = "match_profit.txt";
    char outfilename_mod[255] = "ILP.mod";
    char outfilename_result[255] = "stat.txt";
    char prefix[225] = "data";
    
    int pnum, onum, anum;
    int dum[3];
    int status;
    double k;
    double time1, time2;
    double runningtime, space;
    struct tms timeInfo;
    struct rusage usage;
//    std::ofstream output("stat.txt", std::ios::out);
//    output << "#profit satisfiability runningtime(s) space(MB)"<<std::endl;
//    output.close();

    
    std::ifstream config(configFile, std::ios::in);
    while(config >> pFile >> oFile >> fFile
     >> pnum >> onum >> anum
     >> dum[0] >> k >> dum[1] >> dum[2]){
        if(fork()!=0)return 0;
        times(&timeInfo);
        time1 = timeInfo.tms_utime;
//    time1 = clock();
//    system("cp model.mod ILP.mod");
    wait(&status);
    anum++; 
    std::ifstream ofile(std::string(oFile) , std::ios::in );
    
    std::ifstream pfile(std::string(pFile) , std::ios::in );
    std::ifstream ffile(std::string(fFile) , std::ios::in );
//    std::ifstream ofile(std::string(prefix) + "/"+ std::string(oFile) , std::ios::in );
    
//    std::ifstream pfile(std::string(prefix) + "/"+ std::string(pFile) , std::ios::in );
//    std::ifstream ffile(std::string(prefix) + "/"+ std::string(fFile) , std::ios::in );
    
//    std::ifstream ofile(oFile, std::ios::in);
//    std::ifstream pfile(pFile, std::ios::in);
//    std::ifstream ffile(fFile, std::ios::in);
    std::ofstream outfile_mod(outfilename_mod, std::ios::out);
    outfile_mod <<"param prod; # number of products" <<std::endl
                << "param cust; # number of customers" << std::endl
                << "param matchable; # number of matchable pairs" << std::endl
                << "param k; # satisfiability" << std::endl
                << "param capacity{i in 1..prod}; #capacity at product i" << std::endl
                << "param demand{i in 1..cust}; #demand at customer j" << std::endl
                << "param profit{i in 1..matchable}; #price at pair j" << std::endl
                << "param o{i in 1..matchable}; #customer at pair j" << std::endl
                << "param p{i in 1..matchable}; #product at pair j" << std::endl
                << "var amount{i in 1..matchable} integer >=0, <=matchable;" << std::endl
                << "minimize Cost:" << std::endl
                << "sum{i in 1..matchable} -profit[i]*amount[i];" << std::endl
                << "s.t. Capacity {i in 1..prod}:" << std::endl
                << "sum{j in 1..matchable:i=p[j]} amount[j] <=  capacity[i];" << std::endl
                << "s.t. Demand {i in 1..cust}:" << std::endl
                << "sum{j in 1..matchable: i=o[j]} amount[j] <= demand[i];" << std::endl
                << "s.t. Satisfiability:" << std::endl
                << "sum{j in 1..matchable} amount[j] >= k;" << std::endl
                << "data;" << std::endl;
    outfile_mod << "param prod := " << pnum << ";" << std::endl;
    outfile_mod << "param cust := " << onum << ";" << std::endl;
    outfile_mod << "param k := " << k*onum << ";" << std::endl; 

//    std::ofstream outfile_o(outfilename_o, std::ios::out);
//    std::ofstream outfile_p(outfilename_p, std::ios::out);
//    std::ofstream outfile_c(outfilename_c, std::ios::out);
//    std::ofstream outfile_d(outfilename_d, std::ios::out);
//    std::ofstream outfile_cost(outfilename_cost, std::ios::out);
//    std::ofstream outfile_price(outfilename_price, std::ios::out);
//    std::ofstream outfile_profit(outfilename_profit, std::ios::out);
 //   struct kd_node_t wp[10919711];
//	int o[ONUM][ANUM+3];
//	int p[PNUM][ANUM+3];
    std::vector<std::vector<int> > o(onum, std::vector<int>(anum+2, 1)); 
    std::vector<std::vector<int> > p(pnum, std::vector<int>(anum+2, 1)); 
    std::vector<int> f(anum-1);
   for(int i=0;i< anum-1;i++)ffile >> f[i]; 
 //  std::cout << f[0]; 
    outfile_mod << "param demand:=" <<  std::endl;

	for(int j = 0; j< onum ; j++){
	    for(int i = 0; i< anum+2 ; i++){
            ofile >> o[j][i];
    //        std::cout << o[j][i] << " ";
            // >> link[j] >> u[j][0] >> u[j][1] >> v[j][0] >> v[j][1];
        }
   //     std::cout << std::endl;
        outfile_mod << " " << j+1 << " " << o[j][1];
 //       outfile_price << " " << o[j][0] << " " << o[j][ANUM+2];
    }
        outfile_mod << ";" << std::endl;
   //     outfile_price << ";";
//    outfile_d.close();
 //   outfile_price.close();
    
    outfile_mod << "param capacity:=" << std::endl;

	for(int j = 0; j< pnum ; j++){
	    for(int i = 0; i< anum+2 ; i++){
            int tmp;
            pfile >> tmp;
            p[j][i] = tmp;
    //        std::cout << p[j][i] << " " ;
            // >> link[j] >> u[j][0] >> u[j][1] >> v[j][0] >> v[j][1];
        }
   //     std::cout << std::endl;
        outfile_mod << " " << j+1 << " " << p[j][1];
//        outfile_cost << " " << p[j][0] << " " << p[j][ANUM+2];
    }
        outfile_mod << ";" << std::endl;
//        outfile_cost << ";";
//    outfile_c.close();
//    outfile_cost.close();
    std::vector<int> pairs_p;
    std::vector<int> pairs_o;
    std::vector<int> pairs_profit;
    int match = 1;
 //   int maxcost = 0;
 //   int minprice = 1000000000;
	for(int j = 0; j< pnum ; j++){
	    for(int i = 0; i< onum ; i++){
            bool matchable = true;
            for(int k = 2; k < anum+1; k++){
                if(o[i][k]<p[j][k]&&f[k-2]<0){
                    matchable = false;
                    break;
                }
                if(o[i][k]>p[j][k]&&f[k-2]>0){
                    matchable = false;
                    break;
                }
            }
//            maxcost = std::max(maxcost, p[j][anum+1]);
//            minprice = std::min(minprice, o[i][anum+1]);

            if(o[i][anum+1]<=p[j][anum+1])matchable=false;
            if(matchable){
                pairs_o.push_back(i+1);
                pairs_p.push_back(j+1);
                pairs_profit.push_back(o[i][anum+1]-p[j][anum+1]);
                /*
                    outfile_o << " " << match << " " << o[i][0];
                    outfile_p << " " << match << " " << p[j][0];
                    outfile_profit << " " << match << " " << -p[j][ANUM+2]+o[i][ANUM+2];
                    */
                    match++;
            }
        }
    }
//    std::cout << minprice << " " << maxcost << std::endl; 
    match--;

    outfile_mod << "param matchable := " << match << ";" << std::endl;
    outfile_mod << "param p:=" << std::endl;
    for(int i=1;i<=match;i++)outfile_mod << " " << i << " " << pairs_p[i-1];
    outfile_mod << ";" << std::endl;
    outfile_mod << "param o:=" << std::endl;
    for(int i=1;i<=match;i++)outfile_mod << " " << i << " " << pairs_o[i-1];
    outfile_mod << ";" << std::endl;
    outfile_mod << "param profit:=" << std::endl;
    for(int i=1;i<=match;i++)outfile_mod << " " << i << " " << pairs_profit[i-1];
    outfile_mod << ";" << std::endl;
    outfile_mod << "end;";
    outfile_mod.close();
    pairs_p.clear();
    pairs_o.clear();
    pairs_profit.clear();
    o.clear();
    p.clear();
 //       outfile_o << ";";
 //       outfile_p << ";";
 //       outfile_profit << ";";
//    outfile_o.close();
//    outfile_p.close();
//    outfile_profit.close();
   // system("/csproject/kdd/share/clong/amplide.linux64/ampl ILP.mod");
    system("/csproject/kdd/share/clong/glpk-4.35/examples/glpsol -m ILP.mod --wfreemps ILP.mps --check");
    wait(&status);
    system("/csproject/kdd/share/clong/Cbc-2.9.0/build/bin/cbc ILP.mps solve solu solu.txt > message.txt");
    wait(&status);
    times(&timeInfo);
    time2 = timeInfo.tms_utime;
//    time2 = clock();
    runningtime = (timeInfo.tms_cutime - time1) / sysconf(_SC_CLK_TCK);
//    runningtime = (time2 - time1);
    //runningtime = (time2 - time1)/CLOCKS_PER_SEC;
    std::ifstream solution("solu.txt", std::ios::in); 
    std::string line;
    int satisfiability = 0;
    int profit_sum = 0;
    int a, b;
    int c;
    char d[255];
    std::getline(solution, line);
//    while(!solution.eof()){
    while(solution >> c >> d >> a >> b){
  //      std::cout << " " << c << " " << d << " " << a << " " << b << std::endl;
        satisfiability+=a;
        profit_sum+=pairs_profit[c];
        //profit_sum+=b;
    }
    solution.close();
    std::ofstream state("stat.txt", std::ios::out);

//    sysinfo (&memInfo);
//    long long totalVirtualMem = memInfo.totalram;
    //Add other values in next statement to avoid int overflow on right hand side...
  //  totalVirtualMem += memInfo.totalswap;
//    totalVirtualMem *= memInfo.mem_unit;
//    totalVirtualMem/=(1024*1024); 
    space = getSpace();
    getrusage(RUSAGE_CHILDREN, &usage);
    space += usage.ru_maxrss/1024; 
    state << profit_sum << std::endl << satisfiability << std::endl << std::endl 
        << "0" 
        << std::endl
        << "0" 
        << std::endl
        << runningtime 
        << std::endl 
        << std::endl
        << space 
        << std::endl
        << std::endl
        << "0" 
        << std::endl
        << std::endl
        << "0" 
        << std::endl
        << "0" 
        << std::endl
        << "0" 
        << std::endl
        << "0" 
        << std::endl
        << std::endl
        << "0" 
        << std::endl
        << std::endl
        << "0" 
        << std::endl
        << "0" << std::endl;
    state.close();
    }

    config.close();
    system("rm ILP.mps ILP.mod message.txt solu.txt");
    return 0;
}
