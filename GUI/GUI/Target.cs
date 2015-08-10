namespace GUI
{
    
    public class Target
    {
       
        public Target(string name, int pid)
        {
            Name = name;
            Pid = pid;
        }

        // The name of the target process
        public string Name { get; set; }

        // The process ID
        public int Pid { get; set; }

    }
}
