package com.semestral.eshop.service;

import com.semestral.eshop.domain.Product;

import java.util.List;
import java.util.Optional;

public interface ProductService {
        Product create(Product toAdd);
        Product update(Product toUpdate);
        void delete(Long toDelete);
        Optional<Product> findById(Long toFind );
        List<Product> findAll();
}
