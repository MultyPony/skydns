#include <curl/curl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	mkreq(char *method)
{
	CURL		*curl;
	CURLcode	res;
	char		*head = "{\"id\":0, \"jsonrpc\":\"2.0\",\"method\":\"";
	char		*tail = "\",\"params\":[]}";
	char		*poststr;

	poststr = (char *)malloc(sizeof(char) * (strlen(head) + strlen(method) + strlen(tail)) + 1);
	if (NULL == poststr)
		return (1);
	strcpy(poststr, head);
	strcat(poststr, method);
	strcat(poststr, tail);
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8000/api/json/v2");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, poststr);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	

	curl_global_init(CURL_GLOBAL_ALL);
	mkreq("systemInfo");
	if (argc > 1)		
		mkreq(argv[1]);
	curl_global_cleanup();
	return (0);
}
