package com.trafficmon;

import org.joda.time.DateTime;
import org.joda.time.Hours;
import java.math.BigDecimal;
import java.util.List;

public class CalculateByDuration implements CalculateChargeBehavior {

    private final int maxHoursPerDay = 4;
    private final int entryTime24hFormat = 14;
    private final int midnight = 24;
    private final int chargeIfMoreThanMaxHoursInOneDay = 12;
    private final int chargeBeforeCertainTime = 6;
    private final int chargeAfterCertainTime = 4;
    private int doubleChargeBefore = 0;
    private int doubleChargeAfter = 0;


    private int hoursBetween(DateTime timeOfEntry, DateTime timeOfExit) {
        return Hours.hoursBetween(timeOfEntry,timeOfExit).getHours();
    }

    @Override
    public BigDecimal calculateCharge(List<EventInterface> crossings) {
        EventInterface firstEvent = crossings.get(0);
        boolean beforeFlag = false;
        boolean afterFlag = false;

        int hourOfDayEntry = firstEvent.getTime().getHourOfDay();
        int totalHours=0;

        for (EventInterface crossing : crossings.subList(1, crossings.size())) {
            int hourOfDayExit = crossing.getTime().getHourOfDay();

            if (crossing.getVehicleStatus() == Event.VehicleStatus.ENTERING){
               if(crossing.getTime().getHourOfDay()-hourOfDayEntry >= maxHoursPerDay) {
                    if(hourOfDayEntry < entryTime24hFormat && crossing.getTime().getHourOfDay() <= entryTime24hFormat){
                        doubleChargeBefore +=1;
                    } else if (hourOfDayEntry > entryTime24hFormat && crossing.getTime().getHourOfDay() > entryTime24hFormat){
                        doubleChargeAfter +=1;
                    } else if (hourOfDayEntry <= entryTime24hFormat && crossing.getTime().getHourOfDay() > entryTime24hFormat){
                        doubleChargeBefore -= 1;
                        doubleChargeAfter -= 1;
                    }
                }
            }

            if (crossing.getVehicleStatus() == Event.VehicleStatus.EXITING) {
                totalHours += hoursBetween(firstEvent.getTime(), crossing.getTime());

                if (((hourOfDayEntry > 0) && (hourOfDayEntry < entryTime24hFormat)) && (hourOfDayExit <= entryTime24hFormat)){
                    beforeFlag = true;
                }
                if (hourOfDayEntry >= entryTime24hFormat && (hourOfDayExit>= 14 && hourOfDayExit <= midnight)){
                    afterFlag = true;
                }

                if (hourOfDayEntry < entryTime24hFormat && (hourOfDayExit> 14 && hourOfDayExit <= midnight)){
                    beforeFlag = true;
                }
            }

            firstEvent = crossing;
            hourOfDayEntry = firstEvent.getTime().getHourOfDay();

            if (totalHours >= maxHoursPerDay){
                return BigDecimal.valueOf(chargeIfMoreThanMaxHoursInOneDay);
            }
        }

        BigDecimal charge = new BigDecimal(0);

        if(beforeFlag){
            BigDecimal beforeValue =new BigDecimal(chargeBeforeCertainTime);
            charge = charge.add(beforeValue);
        }

        if(afterFlag){
            BigDecimal afterValue =new BigDecimal(chargeAfterCertainTime);
            charge = charge.add(afterValue);
        }

        if(doubleChargeBefore >= 1){
            BigDecimal beforeDouble = new BigDecimal(doubleChargeBefore *(chargeBeforeCertainTime));
            charge = charge.add(beforeDouble);
        }

        if(doubleChargeAfter >= 1){
            BigDecimal beforeAfter = new BigDecimal(doubleChargeAfter *(chargeAfterCertainTime));
            charge = charge.add(beforeAfter);
        }

        return charge;
    }
}
