package com.trafficmon;
import org.joda.time.DateTime;

class Event implements EventInterface {

    private final DateTime time;
    private VehicleStatus vehicleStatus;

    Event(VehicleStatus vehicleStatus) {
        this.time = new DateTime();
        this.vehicleStatus = vehicleStatus;
    }

    @Override
    public DateTime getTime() {
        return time;
    }


    @Override
    public VehicleStatus getVehicleStatus() {
        return vehicleStatus;
    }
}
