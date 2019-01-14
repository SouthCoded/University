package com.trafficmon;

import org.jmock.integration.junit4.JUnitRuleMockery;
import org.junit.Rule;
import org.junit.Test;

import static org.junit.Assert.*;

public class VehicleTest {

    public Vehicle testVehicle = Vehicle.withRegistration("ABC");

    @Rule
    public JUnitRuleMockery context = new JUnitRuleMockery();

    @Test
    public void testingWithRegistration() {
        assertEquals(testVehicle, Vehicle.withRegistration("ABC"));
    }


    @Test
    public void testingWithRegistrationNotSameNull() {
        assertNotEquals(testVehicle, null);
    }


    @Test
    public void testToString() {
        assertEquals("Vehicle [ABC]", testVehicle.toString());
    }

    @Test
    public void testEquals() {
        assertTrue(testVehicle.equals(Vehicle.withRegistration("ABC")));
        assertFalse(testVehicle.equals(Vehicle.withRegistration("DEF")));
    }

}