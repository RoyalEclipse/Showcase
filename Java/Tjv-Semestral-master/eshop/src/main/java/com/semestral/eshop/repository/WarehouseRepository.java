package com.semestral.eshop.repository;

import com.semestral.eshop.domain.Warehouse;
import org.springframework.data.jpa.repository.JpaRepository;

public interface WarehouseRepository extends JpaRepository<Warehouse, Long> {
}
