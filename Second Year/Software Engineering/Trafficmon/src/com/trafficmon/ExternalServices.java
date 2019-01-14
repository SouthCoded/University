package com.trafficmon;

import java.math.BigDecimal;

class ExternalServices implements ExternalServicesInterface{

    AccountsService registeredCustomerAccountsService;
    PenaltiesService operationsTeam;

    ExternalServices(){
        operationsTeam = OperationsTeam.getInstance();
        registeredCustomerAccountsService = RegisteredCustomerAccountsService.getInstance();
    }

    @Override
    public void investigationInto(Vehicle vehicle) {
        operationsTeam.triggerInvestigationInto(vehicle);
    }

    @Override
    public void penalty(Vehicle vehicle, BigDecimal charge) {
        operationsTeam.issuePenaltyNotice(vehicle,charge);
    }

    @Override
    public void isAccountRegistered(Vehicle vehicle) throws AccountNotRegisteredException {
        registeredCustomerAccountsService.accountFor(vehicle);
    }

    @Override
    public void deductCharge(Vehicle vehicle, BigDecimal charge) throws InsufficientCreditException, AccountNotRegisteredException {
        registeredCustomerAccountsService.accountFor(vehicle).deduct(charge);
    }
}
