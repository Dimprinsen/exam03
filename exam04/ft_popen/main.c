int	main()
{
	int	fd = ft_popen("wc", (char *const []){"wc", NULL}, 'w');
	char *line = "Hello world\nThis is a test\nthird line\n";
	write(fd, line, strlen(line));
	close(fd);
	return (0);
}