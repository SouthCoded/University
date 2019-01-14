package com.trafficmon;

import org.jmock.Expectations;
import org.jmock.integration.junit4.JUnitRuleMockery;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import java.util.ArrayList;
import java.util.Map;

import static junit.framework.TestCase.assertEquals;

public class CongestionChargeSystemTest {

    class CongestionMock extends CongestionChargeSystem{

        CongestionMock(CalculateChargeBehavior chargeBehavior) {
            super(chargeBehavior);
        }

        Map<Vehicle, ArrayList<EventInterface>> getLogMap() {
            return logMap;
        }

        void setMakeCall(Operation makeCall) {
            this.makeCall = makeCall;
        }

    }

    private CongestionMock congestionChargeSystem;
    private CongestionMock congestionChargeSystemMockOperationCall;

    @Rule
    public JUnitRuleMockery context = new JUnitRuleMockery();
    private Operation operationsCallsMock;


    @Before
    public void setUp(){
        // Setting Up fixture
        congestionChargeSystem = new CongestionMock(new CalculateByDuration());
        congestionChargeSystemMockOperationCall = new CongestionMock(new CalculateByDuration());

        operationsCallsMock = context.mock(Operation.class);
        congestionChargeSystemMockOperationCall.setMakeCall(operationsCallsMock);
    }

    @Test
    public void testCallOperationCallSingle(){
        Vehicle firstVehicle = Vehicle.withRegistration("ABC");
        ArrayList<EventInterface> expectedList = new ArrayList<>();

        expectedList.add(new Event(Event.VehicleStatus.ENTERING));
        expectedList.add(new Event(Event.VehicleStatus.EXITING));

        context.checking(new Expectations(){{
            exactly(1).of(operationsCallsMock).operationsTakeAction(with(any(Vehicle.class)), with(any(ArrayList.class)));
        }});

        congestionChargeSystemMockOperationCall.vehicleEnteringZone(firstVehicle);
        congestionChargeSystemMockOperationCall.vehicleLeavingZone(firstVehicle);

        congestionChargeSystemMockOperationCall.calculateCharges();

    }

    @Test
    public void testCallOperationCallMultipleDifference(){
        Vehicle firstVehicle = Vehicle.withRegistration("ABC");
        Vehicle secondVehicle = Vehicle.withRegistration("CYZ");

        context.checking(new Expectations(){{
            exactly(2).of(operationsCallsMock).operationsTakeAction(with(any(Vehicle.class)), with(any(ArrayList.class)));
        }});

        congestionChargeSystemMockOperationCall.vehicleEnteringZone(firstVehicle);
        congestionChargeSystemMockOperationCall.vehicleLeavingZone(firstVehicle);

        congestionChargeSystemMockOperationCall.vehicleEnteringZone(secondVehicle);
        congestionChargeSystemMockOperationCall.vehicleLeavingZone(secondVehicle);

        congestionChargeSystemMockOperationCall.calculateCharges();

    }

    @Test
    public void testCallOperationCallMultipleSame(){
        Vehicle firstVehicle = Vehicle.withRegistration("ABC");

        context.checking(new Expectations(){{
            exactly(1).of(operationsCallsMock).operationsTakeAction(with(any(Vehicle.class)), with(any(ArrayList.class)));
        }});

        congestionChargeSystemMockOperationCall.vehicleEnteringZone(firstVehicle);
        congestionChargeSystemMockOperationCall.vehicleLeavingZone(firstVehicle);

        congestionChargeSystemMockOperationCall.vehicleEnteringZone(firstVehicle);
        congestionChargeSystemMockOperationCall.vehicleLeavingZone(firstVehicle);

        congestionChargeSystemMockOperationCall.calculateCharges();

    }

    @Test
    public void testNewEntryExitEvent(){
        Vehicle firstVehicle = Vehicle.withRegistration("ABC");
        congestionChargeSystem.vehicleEnteringZone(firstVehicle);

        assertEquals(Event.class, congestionChargeSystem.getLogMap().get(firstVehicle).get(0).getClass());
        assertEquals(congestionChargeSystem.getLogMap().get(firstVehicle).get(0).getVehicleStatus(), Event.VehicleStatus.ENTERING);

        congestionChargeSystem.vehicleLeavingZone(firstVehicle);

        assertEquals(Event.class, congestionChargeSystem.getLogMap().get(firstVehicle).get(1).getClass());
        assertEquals(congestionChargeSystem.getLogMap().get(firstVehicle).get(1).getVehicleStatus(), Event.VehicleStatus.EXITING);
    }

    @Test (expected = CalculateChargeCalledMoreThanOneException.class)
    public void testCalculateChargesCalledOnlyOnce() {
        congestionChargeSystem.vehicleEnteringZone(Vehicle.withRegistration("J091 4PY"));
        congestionChargeSystem.vehicleLeavingZone(Vehicle.withRegistration("J091 4PY"));

        congestionChargeSystem.calculateCharges();
        congestionChargeSystem.calculateCharges();
    }
}
