package com.semestral.eshop.controller;

import com.semestral.eshop.domain.Product;
import com.semestral.eshop.domain.dto.ProductDto;
import com.semestral.eshop.domain.mapper.ProductMapper;
import com.semestral.eshop.service.ProductService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.NoSuchElementException;
import java.util.Optional;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/product")
@Api
public class ProductController {
    private final ProductService productService;
    private final ProductMapper productMapper;
    @Autowired
    public ProductController(ProductService productService, ProductMapper productMapper) {
        this.productService = productService;
        this.productMapper = productMapper;
    }

    @GetMapping
    @ApiOperation(value = "get all Products")
    public List<ProductDto> getAll(){
        List<Product> temp = productService.findAll();
        return temp.stream().map(productMapper::toDto).collect(Collectors.toList());
    }

    @GetMapping("/{id}")
    @ApiOperation(value = "get a specific product by id")
    public ResponseEntity<ProductDto> getById(@PathVariable Long id){
        Optional<Product> temp = productService.findById(id);
        Optional<ProductDto> toRet = Optional.ofNullable(productMapper.toDto(temp.get()));
        return toRet.map(ResponseEntity::ok).orElseGet(() -> ResponseEntity.notFound().build());
    }

    @PostMapping
    @ApiOperation(value = "create a new product")
    public ResponseEntity<ProductDto> create( @RequestBody ProductDto toCreate) {
        try{

            Product temp = productMapper.fromDto(toCreate);
            Product toRet = productService.create(temp);
            return ResponseEntity.ok( productMapper.toDto(toRet) );
        }catch ( NoSuchElementException e ){
            return ResponseEntity.notFound().build();
        }

    }

    @PutMapping("/{id}")
    @ApiOperation(value = "update an existing product")
    public ResponseEntity<ProductDto> update(@PathVariable Long id, @RequestBody ProductDto toUpdate){
        Optional<Product> temp = productService.findById(id);
        if( temp.isEmpty() ){
            return ResponseEntity.notFound().build();
        }
        toUpdate.setId(id);
        try {
            ProductDto toRet = productMapper.toDto( productService.update( productMapper.fromDto( toUpdate ) ) );
            return ResponseEntity.ok( toRet );
        }
        catch ( NoSuchElementException e ){
            return ResponseEntity.notFound().build();
        }

    }

    @DeleteMapping("/{id}")
    @ApiOperation(value = "delete an existing product")
    public ResponseEntity<Void> delete(@PathVariable Long id) {
        Optional<Product> temp = productService.findById(id);

        if ( temp.isEmpty() ) {
            return ResponseEntity.notFound().build();
        }
        productService.delete(id);
        return ResponseEntity.noContent().build();
    }
}
