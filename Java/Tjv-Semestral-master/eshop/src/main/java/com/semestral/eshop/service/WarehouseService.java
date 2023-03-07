package com.semestral.eshop.service;

import com.semestral.eshop.domain.Warehouse;

import java.util.List;
import java.util.Optional;

public interface WarehouseService {
    Warehouse create(Warehouse toAdd);
    Warehouse update(Warehouse toUpdate);
    void delete(Long toDelete);
    Optional<Warehouse> findById(Long toFind );
    List<Warehouse> findAll();
}
