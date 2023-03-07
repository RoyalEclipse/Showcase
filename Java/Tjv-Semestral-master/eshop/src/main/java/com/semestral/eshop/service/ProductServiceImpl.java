package com.semestral.eshop.service;

import com.semestral.eshop.domain.Product;
import com.semestral.eshop.repository.ProductRepository;
import com.semestral.eshop.repository.WarehouseRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class ProductServiceImpl implements ProductService{
    private final ProductRepository productRepository;
    private final WarehouseRepository warehouseRepository;

    @Autowired
    public ProductServiceImpl(ProductRepository productRepository,
                              WarehouseRepository warehouseRepository) {
        this.productRepository = productRepository;
        this.warehouseRepository = warehouseRepository;
    }

    @Override
    public Product create(Product toAdd) {
        return productRepository.save(toAdd);
    }

    @Override
    public Product update(Product toUpdate) {
        return productRepository.save(toUpdate);
    }

    @Override
    public void delete(Long toDelete) {
        Product product = productRepository.findById(toDelete).orElse(null);
        assert product != null;
        product.getAvailableAt().forEach(warehouse -> warehouse.getAvailableProducts().remove(product));
        warehouseRepository.saveAll(product.getAvailableAt());
        productRepository.deleteById(toDelete);
    }

    @Override
    public Optional<Product> findById(Long toFind) {
        return productRepository.findById(toFind);
    }

    @Override
    public List<Product> findAll() {
        return productRepository.findAll();
    }
}
