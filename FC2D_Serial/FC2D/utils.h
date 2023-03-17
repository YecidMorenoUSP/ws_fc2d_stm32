#ifndef __UTILS__
#define __UTILS__

#ifdef __cplusplus
extern "C" {
#endif


int __mod__(int x,int y){
    int res = 0;
    if(x>=0)res = x%y;
    else res = (y-1)+((x+1)%y);
    return res;
}

int get_idx(int idx, int offset, int size){
	return __mod__(idx+offset,size);
}


#ifdef __cplusplus
}
#endif

#endif
