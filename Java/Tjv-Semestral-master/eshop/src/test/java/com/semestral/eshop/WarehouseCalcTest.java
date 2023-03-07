package com.semestral.eshop;

import com.semestral.eshop.repository.WarehouseRepositoryCustom;
import org.junit.jupiter.api.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import static org.junit.jupiter.api.Assertions.assertEquals;

@RunWith(SpringRunner.class)
@SpringBootTest
public class WarehouseCalcTest {

    @Autowired
    WarehouseRepositoryCustom warehouseRepositoryCustom;
    @Test
    public void testDistanceCalc(){
        String to = "69.50005:420.666";
        String from = "88.44:77.55";

        double res = warehouseRepositoryCustom.calculateTravelDistance(to, from);

        assertEquals( 85, res);
    }
}
