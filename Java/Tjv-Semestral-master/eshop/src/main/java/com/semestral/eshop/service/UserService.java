package com.semestral.eshop.service;

import com.semestral.eshop.domain.SiteUser;

import java.util.List;
import java.util.Optional;

public interface UserService {
    SiteUser create(SiteUser toAdd);
    SiteUser update(SiteUser toUpdate);
    void delete(Long toDelete);
    Optional<SiteUser> findById(Long toFind );
    List<SiteUser> findAll();

    Optional<SiteUser> findByPasswordAndEmail( String password, String email );


}
