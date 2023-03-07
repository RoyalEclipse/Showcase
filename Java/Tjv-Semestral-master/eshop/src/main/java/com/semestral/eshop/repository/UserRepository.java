package com.semestral.eshop.repository;

import com.semestral.eshop.domain.SiteUser;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.lang.NonNull;

import java.util.Optional;

public interface UserRepository extends JpaRepository<SiteUser, Long> {
    Optional<SiteUser> findByPasswordAndEmail(@NonNull String password, @NonNull String email);
}
