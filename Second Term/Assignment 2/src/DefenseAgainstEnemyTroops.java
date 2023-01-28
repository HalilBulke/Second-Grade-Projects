import java.util.ArrayList;

/**
 * This class accomplishes Mission Nuke'm
 */
public class DefenseAgainstEnemyTroops {
    private ArrayList<Integer> numberOfEnemiesArrivingPerHour;

    public DefenseAgainstEnemyTroops(ArrayList<Integer> numberOfEnemiesArrivingPerHour){
        this.numberOfEnemiesArrivingPerHour = numberOfEnemiesArrivingPerHour;
    }

    public ArrayList<Integer> getNumberOfEnemiesArrivingPerHour() {
        return numberOfEnemiesArrivingPerHour;
    }

    private int getRechargedWeaponPower(int hoursCharging){
        return hoursCharging*hoursCharging;
    }

    /**
     *     Function to implement the given dynamic programming algorithm
     *     SOL(0) <- 0
     *     HOURS(0) <- [ ]
     *     For{j <- 1...N}
     *         SOL(j) <- max_{0<=i<j} [ (SOL(i) + min[ E(j), P(j − i) ] ]
     *         HOURS(j) <- [HOURS(i), j]
     *     EndFor
     *
     * @return OptimalEnemyDefenseSolution
     */
    public OptimalEnemyDefenseSolution getOptimalDefenseSolutionDP(){
        // TODO: YOUR CODE HERE
        int max=0;
        int maxIndex=0;
        int N=getNumberOfEnemiesArrivingPerHour().size();
        int[] SOL = new int[N+1];

        ArrayList<ArrayList<Integer>> Hours = new ArrayList<>();
        ArrayList<Integer> first = new ArrayList<>();
        Hours.add(first);

        for(int j=1;j<=N;j++){
            for(int i =0;i<=j-1;i++){
                if((SOL[i]) + Math.min(getNumberOfEnemiesArrivingPerHour().get(j-1), getRechargedWeaponPower(j-i))>max){
                    max=(SOL[i]) + Math.min(getNumberOfEnemiesArrivingPerHour().get(j-1), getRechargedWeaponPower(j-i));
                    maxIndex=i;
                }
            }
            SOL[j]=(SOL[maxIndex]) + Math.min(getNumberOfEnemiesArrivingPerHour().get(j-1), getRechargedWeaponPower(j-maxIndex));
            ArrayList<Integer> temp = new ArrayList<>(Hours.get(maxIndex));
            temp.add(j);
            Hours.add(temp);

        }
        return new OptimalEnemyDefenseSolution(SOL[N],Hours.get(N));
    }
}
