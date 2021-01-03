import { TestBed } from '@angular/core/testing';

import { PolygonCreationService } from './polygon-creation.service';

describe('PolygonCreationService', () => {
  let service: PolygonCreationService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(PolygonCreationService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
