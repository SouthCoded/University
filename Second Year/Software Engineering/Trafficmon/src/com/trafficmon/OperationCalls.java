package com.trafficmon;

import java.math.BigDecimal;
import java.util.List;

public class OperationCalls implements Operation{

    private CalculateChargeBehavior chargeBehavior;
    ExternalServicesInterface externalServices;

    OperationCalls(CalculateChargeBehavior chargeBehavior){
        this.chargeBehavior = chargeBehavior;
        this.externalServices = new ExternalServices();
    }

    private boolean checkOrderingOf(List<EventInterface> crossings) {
        EventInterface lastEvent;
        lastEvent = crossings.get(0);

        for (EventInterface crossing : crossings.subList(1, crossings.size())) {
            if (crossing.getTime().isBefore(lastEvent.getTime())) {
                return false;
            }
            if (crossing.getVehicleStatus() == Event.VehicleStatus.ENTERING && lastEvent.getVehicleStatus() == Event.VehicleStatus.ENTERING) {
                return false;
            }
            if (crossing.getVehicleStatus() == Event.VehicleStatus.EXITING && lastEvent.getVehicleStatus() == Event.VehicleStatus.EXITING) {
                return false;
            }
            lastEvent = crossing;
        }

        return true;
    }

    public void operationsTakeAction(Vehicle vehicle, List<EventInterface> crossings) {
        if (!checkOrderingOf(crossings)) {
            externalServices.investigationInto(vehicle);
        } else {
            BigDecimal charge = this.chargeBehavior.calculateCharge(crossings);

            boolean isAccountAvailable= false;

            try {
                externalServices.isAccountRegistered(vehicle);
                isAccountAvailable = true;
            }
            catch (AccountNotRegisteredException ice) {
                externalServices.penalty(vehicle, charge);
            }

            if(isAccountAvailable){
                try{
                    externalServices.deductCharge(vehicle, charge);
                } catch (InsufficientCreditException ice){
                    externalServices.penalty(vehicle, charge);
                } catch (AccountNotRegisteredException e) {
                    // Will not called.
                    externalServices.penalty(vehicle, charge);
                }
            }

        }
    }

}
