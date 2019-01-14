package com.trafficmon;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/* Could use https://www.joda.org/joda-time/ to measure "intervals" in calculateCharges()
 * Could use Duration and Period from joda instead of delaySeconds, delayMinutes  */

class CongestionChargeSystem {

    private boolean calcChargeCalledOnce;
    Operation makeCall;
    Map<Vehicle, ArrayList<EventInterface>> logMap;

    CongestionChargeSystem(CalculateChargeBehavior chargeBehavior){
       makeCall = new OperationCalls(chargeBehavior);
       calcChargeCalledOnce = false;
       logMap = new HashMap<>();
    }

    void vehicleEnteringZone(Vehicle vehicle) {
        if(previouslyRegistered(vehicle, this.logMap)) {
            this.logMap.get(vehicle).add(new Event(Event.VehicleStatus.ENTERING));
        }
        else {
            this.logMap.put(vehicle, new ArrayList<>());
            this.logMap.get(vehicle).add(new Event(Event.VehicleStatus.ENTERING));
        }
    }

    void vehicleLeavingZone(Vehicle vehicle) {
        if (previouslyRegistered(vehicle, this.logMap)) {
            Event entry = new Event(Event.VehicleStatus.EXITING);
            this.logMap.get(vehicle).add(entry);
        }
    }

    void calculateCharges() {

        //Assume that a new congestion charge system is created each day and CalculateCharge is called only once per day.
        if(calcChargeCalledOnce) {
            throw new CalculateChargeCalledMoreThanOneException("Cannot run calculateCharges more than once.");
        }
        calcChargeCalledOnce = true;

        for (Vehicle vehicle : this.logMap.keySet()) {
            //Crossings are event logs of entry and exit from zone.
            List<EventInterface> crossings = this.logMap.get(vehicle);
            makeCall.operationsTakeAction(vehicle, crossings);
        }

    }

    private boolean previouslyRegistered(Vehicle vehicle, Map<Vehicle, ArrayList<EventInterface>> eventLog) {
        return eventLog.containsKey(vehicle);
    }

}
