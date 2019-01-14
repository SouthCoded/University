package com.trafficmon;

import org.joda.time.DateTime;

public interface EventInterface {

    DateTime getTime();

    VehicleStatus getVehicleStatus();

    enum VehicleStatus {ENTERING,EXITING}
}
