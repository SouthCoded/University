package com.trafficmon;

import org.joda.time.DateTime;

class FakeEvent implements EventInterface {
    private DateTime now = new DateTime();
    private VehicleStatus vehicleStatus;

    FakeEvent(VehicleStatus vehicleStatus) {
        this.vehicleStatus = vehicleStatus;
    }

    @Override
    public DateTime getTime() {
        return now;
    }

    @Override
    public VehicleStatus getVehicleStatus() {
        return vehicleStatus;
    }

    void setHourTime(int hourOfDay) {
        now = now.withHourOfDay(hourOfDay);
    }

    void setPlusMinutes(int minutes) {
        now = now.plusMinutes(minutes);
    }

    @Override
    public String toString() {
        return "Event: "+this.vehicleStatus+" Time: "+now.toLocalTime();
    }

}

