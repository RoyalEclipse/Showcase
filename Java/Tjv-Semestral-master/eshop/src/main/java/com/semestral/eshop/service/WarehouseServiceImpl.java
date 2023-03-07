package com.semestral.eshop.service;

import com.semestral.eshop.domain.Warehouse;
import com.semestral.eshop.repository.ProductRepository;
import com.semestral.eshop.repository.WarehouseRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.persistence.EntityManager;
import javax.transaction.Transactional;
import java.util.List;
import java.util.Optional;

@Service
public class WarehouseServiceImpl implements WarehouseService{

    private final WarehouseRepository warehouseRepository;
    private final ProductRepository productRepository;

    private final EntityManager entityManager;
    @Autowired
    public WarehouseServiceImpl(WarehouseRepository warehouseRepository,
                                ProductRepository productRepository,
                                EntityManager entityManager) {
        this.warehouseRepository = warehouseRepository;
        this.productRepository = productRepository;
        this.entityManager = entityManager;
    }

    @Override
    public Warehouse create(Warehouse toAdd) {
        return warehouseRepository.save(toAdd);
    }

    @Override
    public Warehouse update(Warehouse toUpdate) {
        return warehouseRepository.save(toUpdate);
    }

    @Override
    @Transactional
    public void delete (Long toDelete) {

        Warehouse warehouse = warehouseRepository.findById(toDelete).orElse(null);
        assert warehouse != null;
        warehouse.getAvailableProducts().forEach(product -> product.getAvailableAt().remove(warehouse));
        productRepository.saveAll(warehouse.getAvailableProducts());
        String deleteQuery = "DELETE FROM product_available_at WHERE available_at_id = " + toDelete;
        entityManager.createNativeQuery(deleteQuery).executeUpdate();
        warehouseRepository.delete(warehouse);
    }

    @Override
    public Optional<Warehouse> findById(Long toFind) {
        return warehouseRepository.findById(toFind);
    }

    @Override
    public List<Warehouse> findAll() {
        return warehouseRepository.findAll();
    }
}
