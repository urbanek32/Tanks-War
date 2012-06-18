#include "stdafx.h"

LoadContent::LoadContent()
{

	


}


#ifdef CPP_0x11
LoadContent* ptr=nullptr;
#else
LoadContent* ptr=NULL;
#endif

LoadContent* LoadContent::GetInstance()
{
	if(ptr==NULL) ptr=new LoadContent();
	return ptr;
}