package com.trafficmon;

import org.jmock.Expectations;
import org.jmock.integration.junit4.JUnitRuleMockery;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;

public class OperationCallsTest {

    class OperationMock extends OperationCalls{

        OperationMock(CalculateChargeBehavior chargeBehavior) {
            super(chargeBehavior);
        }

        void setExternalService(ExternalServicesInterface externalService){
            this.externalServices = externalService;
        }
    }

    class FakeCalculateCharge implements CalculateChargeBehavior {
        BigDecimal value;

        @Override
        public BigDecimal calculateCharge(List<EventInterface> crossings) {
            return value;
        }

        public void setReturnValue(int fakeCharge) {
            value = new BigDecimal(fakeCharge);
        }
    }

    private ExternalServicesInterface externalServicesMock;

    private OperationMock operationMock;
    private OperationMock operationExceedMock;

    private ArrayList<EventInterface> crossing;

    @Rule
    public JUnitRuleMockery context = new JUnitRuleMockery();

    @Before
    public void SetUp(){
        externalServicesMock = context.mock(ExternalServicesInterface.class);

        FakeCalculateCharge fakeCalculateChargeNotExceed = new FakeCalculateCharge();
        fakeCalculateChargeNotExceed.setReturnValue(0);

        operationMock = new OperationMock(fakeCalculateChargeNotExceed);
        operationMock.setExternalService(externalServicesMock);

        FakeCalculateCharge fakeCalculateChargeExceed = new FakeCalculateCharge();
        fakeCalculateChargeExceed.setReturnValue(1000000000);

        operationExceedMock = new OperationMock(fakeCalculateChargeExceed);
        operationExceedMock.setExternalService(externalServicesMock);

        crossing = new ArrayList<>();
    }

    @Test
    public void testInvestigationWrongOrderingEntering(){
        Vehicle vehicle = Vehicle.withRegistration("ABC");
        FakeEvent entryEvent = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        FakeEvent exitEvent = new FakeEvent(EventInterface.VehicleStatus.ENTERING);

        context.checking(new Expectations(){{
            oneOf(externalServicesMock).investigationInto(vehicle);
        }});

        crossing.add(entryEvent);
        crossing.add(exitEvent);

        operationMock.operationsTakeAction(vehicle, crossing);

    }

    @Test
    public void testInvestigationWrongOrderingExiting(){
        Vehicle vehicle = Vehicle.withRegistration("ABC");
        FakeEvent entryEvent = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        FakeEvent exitEvent = new FakeEvent(EventInterface.VehicleStatus.EXITING);

        context.checking(new Expectations(){{
            oneOf(externalServicesMock).investigationInto(vehicle);
        }});

        crossing.add(entryEvent);
        crossing.add(exitEvent);

        operationMock.operationsTakeAction(vehicle, crossing);

    }

    @Test
    public void testEntryAheadOfExit(){
        Vehicle vehicle = Vehicle.withRegistration("A123 XYZ");
        FakeEvent entryEvent = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        entryEvent.setHourTime(17);

        FakeEvent exitEvent = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        exitEvent.setHourTime(11);

        context.checking(new Expectations(){{
            oneOf(externalServicesMock).investigationInto(vehicle);
        }});

        crossing.add(entryEvent);
        crossing.add(exitEvent);

        operationMock.operationsTakeAction(vehicle, crossing);
    }

    @Test
    public void testAccountNotRegistered() throws AccountNotRegisteredException{

        Vehicle vehicle = Vehicle.withRegistration("ABC");
        FakeEvent entryEvent = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        FakeEvent exitEvent = new FakeEvent(EventInterface.VehicleStatus.EXITING);

        context.checking(new Expectations(){{
            oneOf(externalServicesMock).isAccountRegistered(with(any(Vehicle.class)));
            will(throwException(new AccountNotRegisteredException(with(any(Vehicle.class)))));
            oneOf(externalServicesMock).penalty(with(any(Vehicle.class)), with(any(BigDecimal.class)));
        }});

        crossing.add(entryEvent);
        crossing.add(exitEvent);

        operationMock.operationsTakeAction(vehicle, crossing);

    }

    @Test
    public void testAccountRegistered() throws AccountNotRegisteredException, InsufficientCreditException {
        Vehicle vehicle = Vehicle.withRegistration("A123 XYZ");
        FakeEvent entryEvent = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        FakeEvent exitEvent = new FakeEvent(EventInterface.VehicleStatus.EXITING);

        context.checking(new Expectations(){{
            allowing(externalServicesMock).isAccountRegistered(with(any(Vehicle.class)));
            exactly(0).of(externalServicesMock).penalty(with(any(Vehicle.class)), with(any(BigDecimal.class)));
            allowing(externalServicesMock).deductCharge(with(any(Vehicle.class)), with(any(BigDecimal.class)));
        }});

        crossing.add(entryEvent);
        crossing.add(exitEvent);

        operationMock.operationsTakeAction(vehicle, crossing);
    }

    @Test
    public void testIssuePenaltyNotice() throws AccountNotRegisteredException, InsufficientCreditException {
        Vehicle vehicle = Vehicle.withRegistration("A123 XYZ");
        FakeEvent entryEvent = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        FakeEvent exitEvent = new FakeEvent(EventInterface.VehicleStatus.EXITING);

        context.checking(new Expectations(){{
            allowing(externalServicesMock).isAccountRegistered(with(any(Vehicle.class)));
            exactly(0).of(externalServicesMock).penalty(with(any(Vehicle.class)), with(any(BigDecimal.class)));
            allowing(externalServicesMock).deductCharge(with(any(Vehicle.class)), with(any(BigDecimal.class)));
            will(throwException(new InsufficientCreditException(with(any(BigDecimal.class)))));
            exactly(1).of(externalServicesMock).penalty(with(any(Vehicle.class)), with(any(BigDecimal.class)));
        }});

        crossing.add(entryEvent);
        crossing.add(exitEvent);

        operationExceedMock.operationsTakeAction(vehicle, crossing);

    }

}