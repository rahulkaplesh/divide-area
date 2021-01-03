import { ComponentFixture, TestBed } from '@angular/core/testing';

import { PolygonAreaCardComponent } from './polygon-area-card.component';

describe('PolygonAreaCardComponent', () => {
  let component: PolygonAreaCardComponent;
  let fixture: ComponentFixture<PolygonAreaCardComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ PolygonAreaCardComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(PolygonAreaCardComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
