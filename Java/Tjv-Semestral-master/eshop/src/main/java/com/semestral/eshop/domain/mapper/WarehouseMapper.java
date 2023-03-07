package com.semestral.eshop.domain.mapper;

import com.semestral.eshop.domain.Product;
import com.semestral.eshop.domain.Warehouse;
import com.semestral.eshop.domain.dto.WarehouseDto;
import com.semestral.eshop.repository.ProductRepository;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Optional;

@Component
public class WarehouseMapper {
    private final ProductRepository productRepository;

    public WarehouseMapper(
                           ProductRepository productRepository) {
        this.productRepository = productRepository;
    }

    public WarehouseDto toDto(Warehouse warehouse){
        WarehouseDto temp = new WarehouseDto();
        temp.setId(warehouse.getId());
        temp.setCoordinates(warehouse.getCoordinates());

        List<Long> productIds = new ArrayList<>();
        warehouse.getAvailableProducts().forEach( product -> productIds.add(product.getId()) );
        temp.setAvailableProducts(productIds);
        return temp;
    }
    public Warehouse fromDto(WarehouseDto warehouseDto){
        Warehouse temp = new Warehouse();

        List<Product> foundProd = new ArrayList<>();
        for( Long id : warehouseDto.getAvailableProducts() ){
            Optional<Product> found = productRepository.findById(id);
            if( found.isPresent()){
                foundProd.add(found.get());
            }
            else{
                throw new NoSuchElementException("no such product");
            }
        }
        temp.setAvailableProducts(foundProd);
        temp.setId(warehouseDto.getId());
        temp.setCoordinates(warehouseDto.getCoordinates());
        return temp;
    }
}
