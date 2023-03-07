package com.semestral.eshop.controller;

import com.semestral.eshop.domain.SiteUser;
import com.semestral.eshop.domain.dto.SiteUserDto;
import com.semestral.eshop.domain.mapper.SiteUserMapper;
import com.semestral.eshop.service.UserService;
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
@RequestMapping("/user")
@Api
public class UserController {
    private final UserService userService;
    private final SiteUserMapper siteUserMapper;
    @Autowired
    public UserController(UserService userService, SiteUserMapper siteUserMapper) {
        this.userService = userService;
        this.siteUserMapper = siteUserMapper;
    }

    @GetMapping
    @ApiOperation(value = "get all Users")
    public List<SiteUserDto> getAll(){
        List<SiteUser> temp = userService.findAll();
        return temp.stream().map(siteUserMapper::toDto).collect(Collectors.toList());
    }

    @GetMapping("/{id}")
    @ApiOperation(value = "get an existing user by id")
    public ResponseEntity<SiteUserDto> getById( @PathVariable Long id){
        Optional<SiteUser> temp = userService.findById(id);
        try {
            Optional<SiteUserDto> foo = Optional.ofNullable(siteUserMapper.toDto(temp.get()));
            return foo.map(ResponseEntity::ok).orElseGet(() -> ResponseEntity.notFound().build());
        }catch ( NoSuchElementException e ){
            return ResponseEntity.notFound().build();
        }
    }

        @GetMapping("/{email}/{password}")
        @ApiOperation(value="get userId for login")
        public ResponseEntity<Long> getByNameNumber(@PathVariable String email, @PathVariable String password){
            Optional<SiteUser> temp = userService.findByPasswordAndEmail(password, email);
            try {
                Optional<SiteUserDto> foo = Optional.of(siteUserMapper.toDto(temp.get()));
                return ResponseEntity.ok( foo.get().getId() );
            }catch ( NoSuchElementException e ){
                return ResponseEntity.notFound().build();
            }
        }

    @PostMapping
    @ApiOperation(value = "create a new user")
    public SiteUserDto create( @RequestBody SiteUser user) {
        SiteUser temp = userService.create(user);
        return siteUserMapper.toDto(temp);
    }

    @PutMapping("/{id}")
    @ApiOperation(value = "update an existing user")
    public ResponseEntity<SiteUserDto> update(@PathVariable Long id, @RequestBody SiteUserDto user){
        Optional<SiteUser> temp = userService.findById(id);
        if( temp.isEmpty() ){
            return ResponseEntity.notFound().build();
        }
        user.setId(id);
        try{
            SiteUser toRet = userService.update( siteUserMapper.fromDto(user) );
            return ResponseEntity.ok( siteUserMapper.toDto(toRet) );
        }catch ( NoSuchElementException e){
            return ResponseEntity.notFound().build();
        }
    }

    @DeleteMapping("/{id}")
    @ApiOperation(value = "delete an existing user")
    public ResponseEntity<Void> delete(@PathVariable Long id) {
        Optional<SiteUser> temp = userService.findById(id);

        if ( temp.isEmpty() ) {
            return ResponseEntity.notFound().build();
        }
        userService.delete(id);
        return ResponseEntity.noContent().build();
    }
}
