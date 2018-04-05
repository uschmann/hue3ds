#include "include/HttpClient/HttpClient.h"

#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * HttpClient::downloadRepsponse(httpcContext *context) {
    Result ret = 0;
    u32 contentsize=0, readsize=0, size=0;
    u8 *buf;
    
    buf = (u8*)malloc(0x1000);
    httpcGetDownloadSizeState(context, NULL, &contentsize);
	do {
		// This download loop resizes the buffer as data is read.
		ret = httpcDownloadData(context, buf+size, 0x1000, &readsize);
		size += readsize; 
		if (ret == (s32)HTTPC_RESULTCODE_DOWNLOADPENDING){
				//lastbuf = buf; // Save the old pointer, in case realloc() fails.
				buf = (u8*)realloc(buf, size + 0x1000);
			}
	} while (ret == (s32)HTTPC_RESULTCODE_DOWNLOADPENDING);

    // realloc the buffer
    buf = (u8*)realloc(buf, size + 1);
    buf[size + 1] = 0;

    return  (char *) buf;
}

char * HttpClient::get(const char *url) {
    Result ret = 0;
    httpcContext context;
    u32 statuscode;

    ret = httpcOpenContext(&context, HTTPC_METHOD_GET, url, 1);
    ret = httpcSetSSLOpt(&context, SSLCOPT_DisableVerify);
    ret = httpcAddRequestHeaderField(&context, "Connection", "Keep-Alive");
    ret = httpcAddRequestHeaderField(&context, "User-Agent", "httpc-example/1.0.0");
    ret = httpcBeginRequest(&context);
    ret = httpcGetResponseStatusCode(&context, &statuscode);

    char * result = this->downloadRepsponse(&context);
    httpcCloseContext(&context);
    return result;
}

char * HttpClient::put(const char *url, const char* data) {
    Result ret = 0;
    httpcContext context;
    u32 statuscode;

    ret = httpcOpenContext(&context, HTTPC_METHOD_PUT, url, 0);
    ret = httpcSetSSLOpt(&context, SSLCOPT_DisableVerify);
    ret = httpcAddRequestHeaderField(&context, "Connection", "Keep-Alive");
    ret = httpcAddRequestHeaderField(&context, "User-Agent", "httpc-example/1.0.0");
    ret = httpcAddRequestHeaderField(&context, "Content-Type", "application/json");
    ret = httpcAddPostDataRaw(&context, (u32*)data, strlen(data));

    ret = httpcBeginRequest(&context);
    ret = httpcGetResponseStatusCode(&context, &statuscode);

    char * result = this->downloadRepsponse(&context);
    httpcCloseContext(&context);
    return result;
}