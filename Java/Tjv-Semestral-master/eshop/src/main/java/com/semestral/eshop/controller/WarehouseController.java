package com.semestral.eshop.controller;

import com.semestral.eshop.domain.Warehouse;
import com.semestral.eshop.domain.dto.WarehouseDto;
import com.semestral.eshop.domain.mapper.WarehouseMapper;
import com.semestral.eshop.service.WarehouseService;
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
@RequestMapping("/warehouse")
@Api
public class WarehouseController {
    private final WarehouseService warehouseService;
    private final WarehouseMapper warehouseMapper;
    @Autowired
    public WarehouseController(WarehouseService warehouseService, WarehouseMapper warehouseMapper) {
        this.warehouseService = warehouseService;
        this.warehouseMapper = warehouseMapper;
    }

    @GetMapping
    @ApiOperation(value = "get all Warehouses")
    public List<WarehouseDto> getAll(){
        List<Warehouse> temp = warehouseService.findAll();
        return temp.stream().map(warehouseMapper::toDto).collect(Collectors.toList());
    }

    @GetMapping("/{id}")
    @ApiOperation(value = "get a specific warehouse by id")
    public ResponseEntity<WarehouseDto> getById(@PathVariable Long id){
        Optional<Warehouse> temp = warehouseService.findById(id);
        try {
            Optional<WarehouseDto> test = Optional.ofNullable(warehouseMapper.toDto(temp.get()));
            return test.map(ResponseEntity::ok).orElseGet(() -> ResponseEntity.notFound().build());
        }catch( NoSuchElementException e ){
            return ResponseEntity.notFound().build();
        }
    }

    @PostMapping
    @ApiOperation(value = "create a new Warehouse")
    public ResponseEntity<WarehouseDto> create( @RequestBody WarehouseDto toCreate) {
        try {
            Warehouse temp = warehouseMapper.fromDto( toCreate );
            temp = warehouseService.create(temp);
            return ResponseEntity.ok( warehouseMapper.toDto(temp) );
        }
        catch ( NoSuchElementException e){
            return ResponseEntity.notFound().build();
        }
    }

    @PutMapping("/{id}")
    @ApiOperation(value = "update an existing Warehouse")
    public ResponseEntity<WarehouseDto> update(@PathVariable Long id, @RequestBody WarehouseDto toUpdate){
        Optional<Warehouse> temp = warehouseService.findById(id);
        if( temp.isEmpty() ){
            return ResponseEntity.notFound().build();
        }
        toUpdate.setId(id);
        Warehouse toRet = warehouseService.update( warehouseMapper.fromDto( toUpdate ) );
        return ResponseEntity.ok( warehouseMapper.toDto(toRet) );
    }

    @DeleteMapping("/{id}")
    @ApiOperation(value = "delete an existing Warehouse")
    public ResponseEntity<Void> delete(@PathVariable Long id) {
        Optional<Warehouse> temp = warehouseService.findById(id);

        if ( temp.isEmpty() ) {
            return ResponseEntity.notFound().build();
        }
        warehouseService.delete(id);
        return ResponseEntity.noContent().build();
    }
}
