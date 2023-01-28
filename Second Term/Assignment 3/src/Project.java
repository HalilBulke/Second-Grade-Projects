import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Project {
    private final String name;
    private final List<Task> tasks;

    public Project(String name, List<Task> tasks) {
        this.name = name;
        this.tasks = tasks;
    }
    public String getName(){return this.name;}
    /**
     * Schedule all tasks within this project such that they will be completed as early as possible.
     *
     * @return An integer array consisting of the earliest start days for each task.
     */
    public List<Task> getTasks(){return tasks;}

    public int[] getEarliestSchedule() {
        // TODO: YOUR CODE HERE
        int[] erliest=new int[tasks.size()];
        Arrays.fill(erliest, -1);
        Digraph dg=new Digraph(this.tasks.size());
        for(Task t:this.tasks){
            for(int i:t.getDependencies()){
                dg.addEdge(t.getTaskID(),i);
            }
        }
        Topological t=new Topological(dg);
        int index=-1;

        int startTime=0;
        for (int i:t.order()) {//0 1 2 4 3 5
            index+=1;
            if(index==0) {
                erliest[index] = startTime;
            }else {
                startTime=erliest[tasks.get(i).getDependencies().get(0)];
                for(int dep:tasks.get(i).getDependencies()) {
                    if(startTime<erliest[dep]+tasks.get(dep).getDuration())
                        startTime=erliest[dep]+tasks.get(dep).getDuration();
                }
                erliest[i] = startTime;
            }
        }
        return erliest;
    }

    /**
     * @return the total duration of the project in days
     */
    public int getProjectDuration() {
        int projectDuration =this.getEarliestSchedule()[this.getEarliestSchedule().length-1]+tasks.get(this.getEarliestSchedule().length-1).getDuration();
        // TODO: YOUR CODE HERE
        return projectDuration;
    }

    public static void printlnDash(int limit, char symbol) {
        for (int i = 0; i < limit; i++) System.out.print(symbol);
        System.out.println();
    }

    public void printSchedule(int[] schedule) {
        int limit = 65;
        char symbol = '-';
        printlnDash(limit, symbol);
        System.out.println(String.format("Project name: %s", name));
        printlnDash(limit, symbol);

        // Print header
        System.out.println(String.format("%-10s%-45s%-7s%-5s", "Task ID", "Description", "Start", "End"));
        printlnDash(limit, symbol);
        for (int i = 0; i < schedule.length; i++) {
            Task t = tasks.get(i);
            System.out.println(String.format("%-10d%-45s%-7d%-5d", i, t.getDescription(), schedule[i], schedule[i] + t.getDuration()));
        }
        printlnDash(limit, symbol);
        System.out.println(String.format("Project will be completed in %d days.", tasks.get(schedule.length - 1).getDuration() + schedule[schedule.length - 1]));
        printlnDash(limit, symbol);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Project project = (Project) o;

        int equal = 0;

        for (Task otherTask : ((Project) o).tasks) {
            if (tasks.stream().anyMatch(t -> t.equals(otherTask))) {
                equal++;
            }
        }

        return name.equals(project.name) && equal == tasks.size();
    }

}
