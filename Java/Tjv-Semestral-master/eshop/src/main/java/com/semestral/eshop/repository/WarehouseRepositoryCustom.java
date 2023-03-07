package com.semestral.eshop.repository;

import com.semestral.eshop.domain.Product;
import com.semestral.eshop.domain.Warehouse;

import java.util.List;

public interface WarehouseRepositoryCustom {
    Warehouse calculateFurthest(String deliverTo, List<Product> toDeliver );
    int calculateTravelDistance(String deliverTo, String deliverFrom);

    Warehouse findNearest(String deliverTo, Product toDeliver );


}
