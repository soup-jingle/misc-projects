main ()
{
	int pid, i, c, starttime, endtime;
	pid = GetPID();
	Printf("The process PID is %d\n", pid);

	starttime = GetSystemTime() * 100;
	for (i = 0; i < 10000000; i++) {
		c++;
	}
	endtime = GetSystemTime() * 100;

	Printf("Approximate time to execute the loop: %d ms\n", endtime-starttime);
}
