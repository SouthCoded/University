package com.trafficmon;

import org.joda.time.DateTime;
import org.joda.time.Minutes;

import java.math.BigDecimal;
import java.util.List;

public class CalculatePerMinute implements CalculateChargeBehavior{
    private BigDecimal CHARGE_RATE_POUNDS_PER_MINUTE = new BigDecimal(0.05);

    private int minutesBetween(DateTime startTime, DateTime endTime) {
        return Minutes.minutesBetween(startTime, endTime).getMinutes();
    }


    @Override
    public BigDecimal calculateCharge(List<EventInterface> crossings) {

        BigDecimal charge = new BigDecimal(0);

        EventInterface lastEvent = crossings.get(0);

        for (EventInterface crossing : crossings.subList(1, crossings.size())) {

            if (crossing.getVehicleStatus() == Event.VehicleStatus.EXITING) {
                charge = charge.add(
                        new BigDecimal(minutesBetween(lastEvent.getTime(), crossing.getTime()))
                                .multiply(CHARGE_RATE_POUNDS_PER_MINUTE));
            }

            lastEvent = crossing;
        }

        return charge;
    }
}
