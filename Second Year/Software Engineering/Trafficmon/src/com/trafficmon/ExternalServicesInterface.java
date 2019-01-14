package com.trafficmon;

import java.math.BigDecimal;

public interface ExternalServicesInterface {
    void investigationInto(Vehicle vehicle);
    void penalty(Vehicle vehicle, BigDecimal charge);
    void isAccountRegistered(Vehicle vehicle) throws AccountNotRegisteredException;
    void deductCharge(Vehicle vehicle, BigDecimal charge) throws AccountNotRegisteredException, InsufficientCreditException;
}
