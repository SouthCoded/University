package com.trafficmon;

import org.jmock.Expectations;
import org.jmock.integration.junit4.JUnitRuleMockery;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;

import java.math.BigDecimal;

import static org.junit.Assert.*;

public class ExternalServicesTest {

    class ExternalServicesMock extends ExternalServices{
        ExternalServicesMock(){
            super();
        }

        void setRegisteredCustomerAccountsService(AccountsService accountsService){
            this.registeredCustomerAccountsService = accountsService;
        }

        void setOperationTeam(PenaltiesService penaltiesService){
            this.operationsTeam = penaltiesService;
        }
    }

    ExternalServicesMock externalServicesMock = new ExternalServicesMock();
    AccountsService accountsServiceMock;
    PenaltiesService penaltiesServiceMock;

    @Rule
    public JUnitRuleMockery context = new JUnitRuleMockery();


    @Before
    public void SetUp(){
        accountsServiceMock = context.mock(AccountsService.class);
        penaltiesServiceMock = context.mock(PenaltiesService.class);

        externalServicesMock.setRegisteredCustomerAccountsService(accountsServiceMock);
        externalServicesMock.setOperationTeam(penaltiesServiceMock);
    }

    @Test
    public void testInvestigationIntoInvokeTrigger(){
        context.checking(new Expectations(){{
            oneOf(penaltiesServiceMock).triggerInvestigationInto(with(any(Vehicle.class)));
        }});

        externalServicesMock.investigationInto(Vehicle.withRegistration("ABC"));
    }

    @Test
    public void testPenaltyInvokeIssuePenaltyNotice(){
        context.checking(new Expectations(){{
            oneOf(penaltiesServiceMock).issuePenaltyNotice(with(any(Vehicle.class)), with(any(BigDecimal.class)));
        }});

        externalServicesMock.penalty(Vehicle.withRegistration("ABC"), new BigDecimal(10));
    }

    @Test
    public void testIsAccountRegisteredAccountForTrigger() throws AccountNotRegisteredException {
        context.checking(new Expectations(){{
            oneOf(accountsServiceMock).accountFor(with(any(Vehicle.class)));
        }});

        externalServicesMock.isAccountRegistered(Vehicle.withRegistration("ABC"));

    }

    @Test
    public void testDeductCharge() throws AccountNotRegisteredException {
        // Can't Check because we can't mock it
    }


}