#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <array>
#include <typeinfo>

using namespace std;

template<typename T>
ostream& operator<<(ostream& os,const vector<T>&vec){
    auto check = *vec.begin();
    bool cmplx = sizeof(check) > 8;
    const type_info &ti = typeid(check);
    if(cmplx && ti.hash_code() == 5774750460303204477)
        cmplx = false;

    if(cmplx){
        os << "{ \n";
        for(const T& itr: vec){
            os << "    " << itr;
        }
        os << "} \n";
    }else{
        os << "{ ";
        for(const T& itr: vec){
            os << itr << ", ";
        }
        os << "\b\b },\n";
    }
    return os;
}

template<typename KEY,typename VALUE>
ostream& operator<<(ostream& os,const map<KEY,VALUE>&vec){
    auto check = vec.begin()->second;
    bool cmplx = sizeof(check) > 8;
    const type_info &ti = typeid(check);
    if(cmplx && ti.hash_code() == 5774750460303204477)
        cmplx = false;

    if(cmplx){
        os << "{ \n";
        for(auto& itr: vec){
            os << "    " << itr.first << " : ";
            os << itr.second;
        }
        os << "} \n";
    }else{
        os << "{ ";
        for(auto& itr: vec){
            os << itr.first << " : " << itr.second << ", ";
        }
        os << "\b\b },\n";
    }
    return os;
}

int main()
{
    vector<int>v1 = {1,2,3,4,5,9,7,8,9};
    vector<int>v2 = {9,2,5,3,2};
    vector<int>v3 = {1,0,5,3,5,2};
    vector<int>v4 = {8,2,7};
    vector<vector<int>>vec = {v1,v2,v3,v4};
    map<int,vector<int>>umap1;
    umap1[1] = v1;
    umap1[2] = v2;
    map<int,vector<int>>umap2;
    umap2[3] = v3;
    umap2[4] = v4;
    map<int,map<int,vector<int>>>umap;
    umap[45] = umap1;
    umap[54] = umap2;
    cout << umap;
}
