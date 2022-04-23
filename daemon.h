static void skeleton_daemon()
{
	pid_t pid,sid;
	pid=fork();
	if(pid<0)
	{
		exit(EXIT_FAILURE);
	}
	if(pid>0)
	{
		exit(EXIT_SUCCESS);
	}
	sid=setsid();
	if(sid<0)
	{
		exit(EXIT_FAILURE);
	}
	signal(SIGCHLD,SIG_IGN);
	signal(SIGHUP,SIG_IGN);

	pid=fork();
	if(pid<0)
	{
		exit(EXIT_FAILURE);
	}
	if(pid>0)
	{
		exit(EXIT_SUCCESS);
	}

	umask(0);

	chdir("/");
	int x;
	for(x=sysconf(_SC_OPEN_MAX);x>=0;x--)
	{
		close(x);
	}
	openlog("firstdaemon",LOG_PID,LOG_DAEMON);
}
